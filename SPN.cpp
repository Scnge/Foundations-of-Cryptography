//plains 0010011010110111
//keys 00111010100101001101011000111111
/*
0010011010110111
00111010100101001101011000111111
 */
#include<iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

const vector<int> S = {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7};//14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7
const vector<int> P = {1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16};

vector<int> stringToVectorInt(string str)
{
    vector<int> result;
    for(int i = 0; i < str.size(); i++)
        result.push_back(str[i] - 48);
    return result;
}

vector<vector<int>> vectokeys(vector<int> keystxt)
{
    vector<vector<int>> results(log2(keystxt.size()), vector<int>(16));
    for(int i = 0; i < log2(keystxt.size()); i++)
    {
        for(int j = 0; j < 16; j++)
        {
            results[i][j] = keystxt[4*i + j];
        }
    }
    return results;
}

vector<int> invertArray(const vector<int>& arr)
{
    vector<int> inverse(arr.size(), 0);
    for (int i = 0; i < arr.size(); ++i)
    {
        inverse[arr[i]] = i;
    }
    return inverse;
}

vector<int> SPN(vector<vector<int>> keys, vector<int> plaintxt)
{
    //vector<int> S1 = invertArray(S);
    vector<int> w(plaintxt.size()), u(plaintxt.size(), 0), v(plaintxt.size(), 0),
    tempv(plaintxt.size() / 4, 0), result(plaintxt.size());
    w = plaintxt;
    for(int i = 0; i < keys.size()-1; i++)
    {
        for(int j = 0; j < keys[i].size(); j++)//异或
        {
            u[j] = (w[j] + keys[i][j]) % 2;
        }
        int k = 0;
        for(int j = 0; j < plaintxt.size(); j += 4)//S盒置换
        {
            tempv[k] = S[u[j] * 8 + u[j + 1] * 4 + u[j + 2] * 2 + u[j + 3] * 1];
            int index = 3;
            while (index >= 0)
            {
                v[j + index] = tempv[k] % 2;
                tempv[k] /= 2;
                index--;
            }
            k++;
        }
        if(i!=keys.size())
        {
            for (int j = 0; j < keys[i].size(); j++)//P盒代换
            {
                w[P[j] - 1] = v[j];
            }
        }
    }

    for(int j = 0; j < keys[keys.size() - 1].size(); j++)
    {
        result[j] = (v[j] + keys[keys.size() - 1][j]) % 2;
    }

    return result;
}

int main()
{
    string keys, plain;
    vector<int> keystxt, plaintxt, cipytotxt;
    cin >> plain;
    cin >> keys;
    keystxt = stringToVectorInt(keys);
    plaintxt = stringToVectorInt(plain);

    vector<int> result = SPN(vectokeys(keystxt), plaintxt);
    for(int i = 0; i < result.size(); i++)
    {
        cout << result[i];
    }
    return 0;
}