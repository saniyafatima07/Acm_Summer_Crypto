#include<bits/stdc++.h>
#include<vector>
using namespace std;

// uint32_t m[4][4] = {
//     {0x61707865, 0x04030201, 0x08070605, 0x0c0b0a09},
//     {0x100f0e0d, 0x3320646e, 0x01040103, 0x06020905},
//     {0x00000007, 0x00000000, 0x79622d32, 0x14131211},
//     {0x18171615, 0x1c1b1a19, 0x201f1e1d, 0x6b206574}
// };

uint32_t m[4][4] = {
    {0x00000000, 0x00000000, 0x00000000, 0x00000000},
    {0x00000000, 0x00000000, 0x00000000, 0x00000001},
    {0x00000000, 0x00000000, 0x00000000, 0x00000000},
    {0x00000000, 0x00000000, 0x00000000, 0x00000000}
};

uint32_t rotl(uint32_t v, int n) {
    return (v << n) | (v >> (32-n));
}

// void round_function(uint32_t m[4][4]){
//     for(int i=0; i<4; i++){
//         m[(1+i)%4][i]^=rotl(m[(4+i)%4][i] + m[(3+i)%4][i], 7);
//         m[(2+i)%4][i]^=rotl(m[(1+i)%4][i] + m[(4+i)%4][i], 9);
//         m[(3+i)%4][i]^=rotl(m[(2+i)%4][i] + m[(1+i)%4][i], 13);
//         m[(4+i)%4][i]^=rotl(m[(3+i)%4][i] + m[(2+i)%4][i], 18);
//     }
// }

void round_function(uint32_t m[4][4]){
    for(int i=0; i<4; i++){
        m[(1+i)%4][i]^=rotl(m[(4+i)%4][i] ^ m[(3+i)%4][i], 7);
        m[(2+i)%4][i]^=rotl(m[(1+i)%4][i] ^ m[(4+i)%4][i], 9);
        m[(3+i)%4][i]^=rotl(m[(2+i)%4][i] ^ m[(1+i)%4][i], 13);
        m[(4+i)%4][i]^=rotl(m[(3+i)%4][i] ^ m[(2+i)%4][i], 18);
    }
}

void transpose(uint32_t m[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 4; j++)
            swap(m[i][j], m[j][i]);
}

int main() {
    round_function(m);

    cout<< "After Odd Round" << "\n";
    cout << "+------------+------------+------------+------------+" << endl;
    for (uint32_t i = 0; i < 4; i++) {
        cout << "|";
        for (uint32_t j = 0; j < 4; j++) {          // fixed: j<4
            cout << " 0x" << hex << setw(8) << setfill('0') 
                 << m[i][j] << " |";
        }
        cout << "\n+------------+------------+------------+------------+" << endl;
    }

    // transpose(m);
    // round_function(m);
    // transpose(m);
    // cout<< "After Even Round" << "\n";
    // cout << "+------------+------------+------------+------------+" << endl;
    // for (uint32_t i = 0; i < 4; i++) {
    //     cout << "|";
    //     for (uint32_t j = 0; j < 4; j++) {          // fixed: j<4
    //         cout << " 0x" << hex << setw(8) << setfill('0') 
    //              << m[i][j] << " |";
    //     }
    //     cout << "\n+------------+------------+------------+------------+" << endl;
    // }
}