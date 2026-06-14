#include <iostream>
#include <vector>
#include <string.h>
#include <bitset>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <algorithm>
#include <array>
using namespace std;

static const int SBOX[8][4][16] = {
    // S1
    {
        {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
        { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
        { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
        {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
    },
    // S2
    {
        {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
        { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
        { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
        {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}
    },
    // S3
    {
        {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
        {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
        {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
        { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
    },
    // S4
    {
        { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
        {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
        {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
        { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
    },
    // S5
    {
        { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
        {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
        { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
        {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}
    },
    // S6
    {
        {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
        {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
        { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
        { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}
    },
    // S7
    {
        { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
        {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
        { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
        { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}
    },
    // S8
    {
        {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
        { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
        { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
        { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}
    }
};

string xorStrings(const string& a, const string& b) {
    string result(a.size(), '0');
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = ((a[i] - '0') ^ (b[i] - '0')) ? '1' : '0';
    }
    return result;
}

string decimalToBinary(int num){
    string binary(6, '0');

    while(num>0){
        binary += (num%2) + '0';
        num /= 2;
    }
    reverse(binary.begin(), binary.end());
    return binary;
}

int extract_row(int input)
{
    string binary = decimalToBinary(input);
    int rowIndex = 2* (binary[0] - '0') + (binary[5] - '0');
    return rowIndex;
}

int extract_col(int input)
{
    string binary = decimalToBinary(input);
    int columnIndex = 8* (binary[1] - '0') + 4*(binary[2] - '0') + 2*(binary[3]-'0') + (binary[4]-'0');
    return columnIndex;
}

vector<vector<int>> compute_DDT(const int SBOX[4][16]) {
    vector<vector<int>>ddt_table(64, vector<int>(16, 0));
        for(int i=0; i<64; i++){
            int row_p1 = extract_row(i);
            int col_p1 = extract_col(i);
            int c1 = SBOX[row_p1][col_p1];

            for(int j=0; j<64; j++){
                int row_p2 = extract_row(j);
                int col_p2 = extract_col(j);       
                int c2 = SBOX[row_p2][col_p2];

                int diff_p = i^j;
                int diff_c = c1^c2;

                ddt_table[diff_p][diff_c]++;
            }
        }
    return ddt_table;
}

void printDDT(const vector<vector<int>>& ddt)
{
    cout << setw(4) << "";
    for(int dy = 0; dy < 16; dy++){
        cout << setw(4) << dy;
    }
    cout << '\n';

    for(int dx = 0; dx < 64; dx++){
        cout << setw(4) << dx;

        for(int dy = 0; dy < 16; dy++){
            cout << setw(4) << ddt[dx][dy];
        }
        cout << '\n';
    }
}

int main() {
    for(int i=0; i<8; i++) {
        auto ddt = compute_DDT(SBOX[i]);
        printDDT(ddt);
        cout<< "\n";
    }
}