#include <iostream>
using namespace std;

string decryptCaesar(string text, int shift) {
    for (char &c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int pos = c - base;
            int s = (pos-shift+26)%26;
            c = s + base;
        }
    }
    return text;
}

string atbashCipher (string text) {
    string res = "";
    for (char c : text){
        if(c>='A' && c<='Z')
            res += (char)(('Z'+'A') - c);

        else if(c>='a' && c<='z')
            res += (char)(('z'+'a') - c);

        else
            res += " ";
    }
    return res;
}

string encryptAffineCipher (string message, int a, int b) {
    int x, temp;
    string res;
    for (char c: message) {
        if(c>='a' && c<='z'){
            x = c - 'a';
            temp = ((a*x + b))%26;
            temp += 'a';
            res += temp;
        }
        else if(c>='A' && c<='Z') {
            x  = c - 'A';
            temp = ((a*x) + b) % 26;
            temp += 'A';
            res += temp;
        }
        else{
            res += " ";
        }
    }
    return res;
}

int modInverse(int a) {
    for(int i=1; i<26; i++){
        if((a*i)%26 == 1)
            return i;
    }
    return -1;
}

string decryptAffineCipher (string message, int a, int b) {
    string res="";
    int y,temp,aInv;
    for(char c: message) {
        if(c>='a' && c<='z'){
            y = c - 'a';
            aInv = modInverse(a);
            temp = (aInv * (y - b + 26)) % 26;
            res += temp + 'a';
        }
        else if(c>='A' && c<='Z'){
            y = c - 'A';
            aInv = modInverse(a);
            temp = (aInv * (y - b + 26)) % 26;
            res += temp + 'A';
        }
        else{
            res += ' ';
        }
    }
    return res;
}

int main() {
    int shift;

    // string text1 = "Fdhvdu flskhu lv rqh ri wkh hduolhvw dqg vlpsohvw phwkrgv ri hqfubswlrq. Lw zrunv eb vkliwlqj hdfk ohwwhu lq wkh sodlqwhaw eB d ilahg qxpehu ri srvlwlrqv lq wkh doskdehw. Dowkrxjk lw lv hdvb wr lpsohphqw, lw surylghv yhub olwwoh vhfxulwb djdlqvw prghuq fubswdqdobvlv whfkqltxhv. Qhyhuwkhohvv, lw uhpdlqv d xvhixo hgxfdwlrqdo wrro iru xqghuvwdqglqj wkh edvlf frqfhswv ri fodvvlfdo fubswrjudskb";
    // string text2 = "Ynulpkcnwlddu eo w bqjzwiajpwh pkkh ej ejbkniwpekj oayqnepu. Ep dahlo lnkpayp iaoowcao bnki qjwqpdknevaz wyyaoo xu pnwjobkniejc lhwej pazp ejpk wj qjnawzwxha bkni. Whpdkqcd ikzanj yeldano wna iqyd ikna ykilhaz, deopkneywh oydaiao oqyd wo pda odebp yeldan naiwej qoabqh bkn hawnjejc pda xwoeyo kb ajynulpekj wjz ynulpwjwhuoeo.";
    // for(int i=0; i<=26; i++){
    //     cout<< i << "\n";
    //     cout << "Decrypted text1: " << decryptCaesar(text1, i) << "\n";

    //     cout<< i << "\n";
    //     cout << "Decrypted text2: " << decryptCaesar(text2, i) << "\n";
    // }

    string text3 = "GSRH RH Z HVXIVG NVHHZTV";
    string text4 = "Xibkgltizksb rh gsv hxrvmxv lu hvxfirmt rmulinzgrlm yb gizmhulinrmt rg rmgl z ulin gszg rh wruurxfog gl fmwvihgzmw drgslfg gsv kilkvi pvb. Xozhhrxzo xrksvih hfxs zh gsv Zgyzhs xrksvi kilerwv z hrnkov rmgilwfxgrlm gl gsv xlmxvkgh lu vmxibkgrlm zmw wvxibkgrlm. Zogslfts rg luuvih orggov kizxgrxzo hvxfirgb, rg ivnzrmh zm rnkligzmg vwfxzgrlmzo gllo uli hgfwbrmt gsv srhglib zmw velofgrlm lu xibkgltizksrx gvxsmrjfvh.";
    cout << "Decrypted text: " << atbashCipher(text3) << "\n";
    cout << "Decrypted text: " << atbashCipher(text4) << "\n";

    string text5 = "HELLO";
    cout<< "Encrypted text: " << encryptAffineCipher(text5, 5, 8) << "\n";

    string text6 = "SPYFZAMPIFRY WU ZRC USWCVSC AH UCSEPWVM WVHAPQIZWAV NY ZPIVUHAPQWVM WZ WVZA I HAPQ ZRIZ WU XWHHWSELZ ZA EVXCPUZIVX OWZRAEZ ZRC FPAFCP GCY. SLIUUWSIL SWFRCPU UESR IU ZRC IHHWVC SWFRCP FPAJWXC I UWQFLC WVZPAXESZWAV ZA ZRC SAVSCFZU AH CVSPYFZWAV IVX XCSPYFZWAV.";
    cout<< "Decrypted text:" << decryptAffineCipher(text6, 5, 8) << "\n";
    
    return 0;
}  