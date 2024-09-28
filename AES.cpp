/*
000102030405060708090a0b0c0d0e0f
00112233445566778899aabbccddeeff
*/
//69C4E0D86A7B0430D8CDB78070B4C55A
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

const vector<unsigned char> SBox = {
        0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
        0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
        0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
        0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
        0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
        0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
        0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
        0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
        0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
        0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
        0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
        0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
        0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
        0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
        0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
        0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16};
const vector<unsigned char> Rcon = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

//转化
unsigned char StrtoChar(string str) {
    unsigned char result;
    char high, low;
    if (str[0] >= 'A' && str[0] <= 'Z')
        high = str[0] + ('a' - 'A');
    else
        high = str[0];
    if (str[1] >= 'A' && str[1] <= 'Z')
        low = str[1] + ('a' - 'A');
    else
        low = str[1];

    unsigned char highByte, lowByte;
    if (isdigit(high))
        highByte = high - '0';
    else{
        if(high >= 'a' && high <= 'z')
            highByte = (high- 32) - 'A' + 10;
        else
        highByte = high - 'A' + 10;
    }

    if (isdigit(low))
        lowByte = low - '0';
    else{
        if(low >= 'a' && low <= 'z')
            lowByte = (low- 32) - 'A' + 10;
        else
            lowByte = low - 'A' + 10;
    }

    result = (highByte << 4) | lowByte;

    return result;
}
string ChartoNum(vector<unsigned char> ch) {
    string result;
    for(int i = 0; i < ch.size(); ++i) {
        unsigned char b = ch[i];
        string temp(2, ' ');
        const string targets = "0123456789ABCDEF";

        temp[0] = targets[(b / 16) - ((b / 16) / 16) * 16];
        temp[1] = targets[b % 16];

        result += temp;
    }
    return result;
}
//乘法
unsigned char Multiply(unsigned char a, unsigned char b) {
    unsigned char result = 0;
    for (int i = 0; i < 8; ++i) {
        if (b % 2 == 1)
            result = result ^ a;
        bool high_bit_set = a >= 128;
        a <<= 1;
        if (high_bit_set)
            a = a ^ 0x1B;
        b /= 2;
    }
    return result;
}
//密钥拓展
vector<vector<unsigned char>> KeyExpansion(vector<unsigned char> keyBytes) {
    vector<vector<unsigned char>> result;
    for (int i = 0; i < keyBytes.size(); i += 4)
        result.push_back({keyBytes[i], keyBytes[i + 1], keyBytes[i + 2], keyBytes[i + 3]});

    for (int i = 4; i < 44; ++i) {
        vector<unsigned char> temp = result[i - 1];

        if (i % 4 == 0) {
            vector<unsigned char> rotated = {temp[1], temp[2], temp[3], temp[0]};
            temp = {SBox[rotated[0]], SBox[rotated[1]], SBox[rotated[2]], SBox[rotated[3]]};
            temp[0] ^= Rcon[i / 4 - 1];
        }

        vector<unsigned char> newu(4);
        for (int j = 0; j < 4; ++j) {
            newu[j] = result[i - 4][j] ^ temp[j];
        }
        result.push_back(newu);
    }

    return result;
}

//1
void SubBytes(vector<unsigned char>& ch) {
    for (int i = 0; i < ch.size(); ++i)
        ch[i] = SBox[ch[i]];
}
//2
void ShiftRows(vector<unsigned char>& ch) {
    vector<unsigned char> temp = ch;
    ch[1] = temp[5];
    ch[5] = temp[9];
    ch[9] = temp[13];
    ch[13] = temp[1];
    ch[2] = temp[10];
    ch[6] = temp[14];
    ch[10] = temp[2];
    ch[14] = temp[6];
    ch[3] = temp[15];
    ch[7] = temp[3];
    ch[11] = temp[7];
    ch[15] = temp[11];
}
//3
void MixColumns(vector<unsigned char>& ch) {
    for (int i = 0; i < 16; i += 4) {
        vector<unsigned char> col = {ch[i], ch[i+1], ch[i+2], ch[i+3]};
        ch[i] = Multiply(col[0], 2) ^ Multiply(col[1], 3) ^ col[2] ^ col[3];
        ch[i+1] = col[0] ^ Multiply(col[1], 2) ^ Multiply(col[2], 3) ^ col[3];
        ch[i+2] = col[0] ^ col[1] ^ Multiply(col[2], 2) ^ Multiply(col[3], 3);
        ch[i+3] = Multiply(col[0], 3) ^ col[1] ^ col[2] ^ Multiply(col[3], 2);
    }
}
//4
void AddRoundKey(vector<unsigned char>& ch, const vector<vector<unsigned char>>& expandedKey, int round) {
    for (int i = 0; i < 16; i++) {
        ch[i] ^= expandedKey[round * 4 + i / 4][i % 4];
    }
}

//AES
string AES(string plain, string key) {
    vector<unsigned char> plaintxt;
    //vector<unsigned char> current;
    vector<unsigned char> keytxt;
    
    for (int i = 0; i < plain.length(); i += 2)
        plaintxt.push_back(StrtoChar(plain.substr(i, 2)));
    for (int i = 0; i < key.length(); i += 2)
        keytxt.push_back(StrtoChar(key.substr(i, 2)));

    vector<vector<unsigned char>> expandedKey = KeyExpansion(keytxt);
    AddRoundKey(plaintxt, expandedKey, 0);

    for (int round = 1; round < 10; ++round) {
        SubBytes(plaintxt);
        ShiftRows(plaintxt);
        MixColumns(plaintxt);
        AddRoundKey(plaintxt, expandedKey, round);
    }
    
    SubBytes(plaintxt);
    ShiftRows(plaintxt);
    AddRoundKey(plaintxt, expandedKey, 10);

    return ChartoNum(plaintxt);
}

int main() {
    string key, plaintext;
    cin >> key;
    cin >> plaintext;

    string cipher = AES(plaintext, key);

    cout << cipher;

    return 0;
}