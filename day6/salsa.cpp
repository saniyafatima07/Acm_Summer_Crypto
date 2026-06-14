#include<bits/stdc++.h>
#include<vector>
using namespace std;

void fill_random(uint32_t m[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = ((uint32_t)rand() << 16) | rand();
        }
    }
}

uint32_t rotl(uint32_t v, int n) {
    return (v << n) | (v >> (32-n));
}

void round_function(uint32_t m[4][4]){
    for(int i=0; i<4; i++){
        m[(1+i)%4][i]^=rotl(m[(4+i)%4][i] + m[(3+i)%4][i], 7);
        m[(2+i)%4][i]^=rotl(m[(1+i)%4][i] + m[(4+i)%4][i], 9);
        m[(3+i)%4][i]^=rotl(m[(2+i)%4][i] + m[(1+i)%4][i], 13);
        m[(4+i)%4][i]^=rotl(m[(3+i)%4][i] + m[(2+i)%4][i], 18);
    }
}

void transpose(uint32_t m[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 4; j++)
            swap(m[i][j], m[j][i]);
}

int main() {
    int count = 0;
    srand(time(0));
    uint32_t m[4][4];
    uint32_t copy[4][4];

    for(int i=0; i<1000; i++) {
        fill_random(m);

        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                copy[r][c] = m[r][c];
            }
        }

        copy[1][3] ^= (1u << 31);

        for(int r = 0; r < 4; r++) {

            round_function(m);
            transpose(copy);
            round_function(copy);
            transpose(copy);

            uint32_t xored[4][4];

            for(int row = 0; row < 4; row++) {
                for(int col = 0; col < 4; col++) {
                    xored[row][col] = m[row][col] ^ copy[row][col];
                }
            }

            if (((xored[1][3] >> 31) & 1) == 1)
                count++;
        }
    }
    cout<< count << "\n";
}