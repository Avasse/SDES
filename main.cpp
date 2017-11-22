#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>
#include <iterator>

using namespace std;

const int SBox0[4][4] = {{1,3,0,3}, {0,2,2,1}, {3,1,1,3}, {2,0,3,2}};
const int SBox1[4][4] = {{0,2,3,2}, {1,0,0,1}, {2,1,1,0}, {3,3,0,3}};

vector<int> P8switch(vector<int> key){
    vector<int> P8 = {key[5], key[2], key[6], key[3], key[7], key[4], key[9], key[8]};
    return P8;
}

vector<int> getK2(vector<int> P10){
    vector<int> K2 = {P10[2], P10[3], P10[4], P10[0], P10[1], P10[7], P10[8], P10[9], P10[5], P10[6]};
    K2 = P8switch(K2);
    return K2;
}

vector<int> getP10(vector<int> key){
    vector<int> P10 = {key[2], key[4], key[1], key[6], key[3], key[9], key[0], key[8], key[7], key[5]};
    return P10;
}

vector<int> rotateP10(vector<int> P10){
    vector<int> rotatedP10 = {P10[1], P10[2], P10[3], P10[4], P10[0], P10[6], P10[7], P10[8], P10[9], P10[5]};
    return rotatedP10;
}

vector<int> uCharToOctet(unsigned char character) {
    bitset<8> octet(character);
    vector<int> res(8);
    int k = octet.size() - 1;
    for (int i = 0; i < octet.size(); i++){
        res[k] = octet.test(i);
        k--;
    }
    return res;
}

vector<int> getIP(vector<int> octet) {
    vector<int> IP = {octet[1], octet[5], octet[2], octet[0], octet[3], octet[7], octet[4], octet[6]};
    return IP;
}

vector<int> getEP(vector<int> octet) {
    octet = {octet[4], octet[5], octet[6], octet[7]};
    vector<int> EP = {octet[3], octet[0], octet[1], octet[2], octet[1], octet[2], octet[3], octet[0]};
    return EP;
}

vector<int> XoR(vector<int> octet, vector<int> K) {
    vector<int> res(8);
    for (int i = 0; i < octet.size(); i++) {
        res[i] = (octet[i] xor K[i]);
    }
    return res;
}

vector<int> getS0(vector<int> octet) {
    string castLine = to_string(octet[0]) + to_string(octet[3]);
    string castColumn = to_string(octet[1]) + to_string(octet[2]);
    bitset<2> octetLine(castLine);
    bitset<2> octetColumn(castColumn);
    auto line = (int) octetLine.to_ulong();
    auto column = (int) octetColumn.to_ulong();
    int S0 = SBox0[column][line];
    bitset<2> convertS0(S0);
    string test = convertS0.to_string();
    vector<int> res = {convertS0[1], convertS0[0]};
    return res;
}

vector<int> getS1(vector<int> octet) {
    string castLine = to_string(octet[4]) + to_string(octet[7]);
    string castColumn = to_string(octet[5]) + to_string(octet[6]);
    bitset<2> octetLine(castLine);
    bitset<2> octetColumn(castColumn);
    auto line = (int) octetLine.to_ulong();
    auto column = (int) octetColumn.to_ulong();
    int S1 = SBox1[column][line];
    bitset<2> convertS1(S1);
    vector<int> res = {convertS1[1], convertS1[0]};
    return res;
}

vector<int> getP4(vector<int> S0, vector<int> S1) {
    vector<int> P4 = {S0[1], S1[1], S1[0], S0[0]};
    return P4;
}

vector<int> getFK(vector<int> P4, vector<int> IP) {
    vector<int> FK(8);
    for (int i = 0; i < P4.size(); i++) {
        FK[i] = (P4[i] xor IP[i]);
    }
    FK = {FK[0], FK[1], FK[2], FK[3], IP[4], IP[5], IP[6], IP[7]};
    return FK;
}

vector<int> getSW(vector<int> FK) {
    vector<int> SW = {FK[4], FK[5], FK[6], FK[7], FK[0], FK[1], FK[2], FK[3]};
    return SW;
}

vector<int> getIPminOne(vector<int> octet) {
    vector<int> IPminOne = {octet[3], octet[0], octet[2], octet[4], octet[6], octet[1], octet[7], octet[5]};
    return IPminOne;
}

int decryptOctect(vector<int> octet) {
    stringstream castString;
    copy(octet.begin(), octet.end(), ostream_iterator<int>(castString, ""));
    bitset<8> charOctet(castString.str().c_str());
    int charDecimal = (int) charOctet.to_ulong();
    return charDecimal;
}


int main() {
    unsigned char A = 'A', e = 'e';
    vector<int> key {1, 1, 1, 1, 0, 1, 1, 0, 0, 1};
    vector<int> P10 = getP10(key);
    vector<int> rotatedP10 = rotateP10(P10);
    vector<int> K1 = P8switch(rotatedP10);
    vector<int> K2 = getK2(rotatedP10);

    vector<int> AOctet = uCharToOctet(A);
    vector<int> AIP = getIP(AOctet);
    vector<int> AEP = getEP(AIP);
    vector<int> AEPxorK1 = XoR(AEP, K1);
    vector<int> AS0 = getS0(AEPxorK1);
    vector<int> AS1 = getS1(AEPxorK1);
    vector<int> AP4 = getP4(AS0, AS1);
    vector<int> AFK = getFK(AP4, AIP);
    vector<int> ASW = getSW(AFK);
    vector<int> ASWEP = getEP(ASW);
    vector<int> ASWEPxorK2 = XoR(ASWEP, K2);
    vector<int> ASWS0 = getS0(ASWEPxorK2);
    vector<int> ASWS1 = getS1(ASWEPxorK2);
    vector<int> ASWP4 = getP4(ASWS0, ASWS1);
    vector<int> ASWFK = getFK(ASWP4, ASW);
    vector<int> ASWIPminOne = getIPminOne(ASWFK);
    int ADecrypted = decryptOctect(ASWIPminOne);

    vector<int> eOctet = uCharToOctet(e);
    vector<int> eIP = getIP(eOctet);
    vector<int> eEP = getEP(eIP);
    vector<int> eEPxorK1 = XoR(eEP, K1);
    vector<int> eS0 = getS0(eEPxorK1);
    vector<int> eS1 = getS1(eEPxorK1);
    vector<int> eP4 = getP4(eS0, eS1);
    vector<int> eFK = getFK(eP4, eIP);
    vector<int> eSW = getSW(eFK);
    vector<int> eSWEP = getEP(eSW);
    vector<int> eSWEPxorK2 = XoR(eSWEP, K2);
    vector<int> eSWS0 = getS0(eSWEPxorK2);
    vector<int> eSWS1 = getS1(eSWEPxorK2);
    vector<int> eSWP4 = getP4(eSWS0, eSWS1);
    vector<int> eSWFK = getFK(eSWP4, eSW);
    vector<int> eSWIPminOne = getIPminOne(eSWFK);
    int eDecrypted = decryptOctect(eSWIPminOne);

    cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_HELLO THIS IS A SDES ENCRYPTION WITH 2 PREDEFINED CHARS *_*_*_*_*_*_*_*_*_*_*_*_*_*_*" << endl << endl;

    cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_CHAR 'A' RESULTS_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*" << endl;
    cout << "BINARY ENCYPTED CHAR : ";
    for (int i = 0; i < 8; ++i) {
        cout << ASWIPminOne[i];
    }
    cout << endl << "DECIMAL ENCRYPTED CHAR : " << ADecrypted << endl;
    cout << "CRYPTED CHAR : COMPILER CAST ERROR, STATIC ANSWER : Û" << endl << endl;

    cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_CHAR 'e' RESULTS_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*" << endl;
    cout << "BINARY ENCYPTED CHAR : ";
    for (int i = 0; i < 8; ++i) {
        cout << eSWIPminOne[i];
    }
    cout << endl << "DECIMAL ENCRYPTED CHAR : " << eDecrypted << endl;
    cout << "CRYPTED CHAR : COMPILER CAST ERROR, STATIC ANSWER : \u0096" << endl << endl;

    cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_ENTER SOMETHING TO CLOSE PROGRAM, THANKS YOU_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*" << endl << endl;
    int close;
    cin >> close;
    return 0;
}