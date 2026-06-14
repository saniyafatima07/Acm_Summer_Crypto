#ifndef HELPER_H
#define HELPER_H
#include<bits/stdc++.h>
using namespace std;

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

int dot_product(int value, int mask)
{
    return __builtin_popcount(value & mask) & 1;
}

vector<vector<int>> compute_lat(const int sbox[4][16])
{
    vector<vector<int>> lat(64, std::vector<int>(16, 0));

    for(int i=0; i<64; i++){
        int rowInd = extract_row(i);
        int colInd = extract_col(i);
        int sBoxInd = sbox[rowInd][colInd];

        for(int j=0; j<64; j++){
            int alpha_x = dot_product(j,i);
            for(int k=0; k<16; k++){
                int beta_y = dot_product(k,sBoxInd);

                if(alpha_x == beta_y){
                    lat[j][k]++;
                }
            }
        }
        
    }

    for(int j=0; j<64; j++){
        for(int k=0; k<16; k++){
            lat[j][k] -= 32;
        }
    }
    return lat;
}

#endif