#include <iostream>
#include <vector>
#include <bitset>

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
    bitset<8> octet = character;
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

vector<int> xorK1(vector<int> octet, vector<int> K1) {
    vector<int> res(8);
    for (int i = 0; i < octet.size(); i++) {
        res[i] = (octet[i] xor K1[i]);
    }
    return res;
}

vector<int> getS0(vector<int> octet) {
    vector<int> res(8);
    string castLine = to_string(octet[0]) + to_string(octet[1]);
    string castColumn = to_string(octet[1]) + to_string(octet[2]);
    bitset<2> octetLine(castLine);
    bitset<2> octetColumn(castColumn);
    int line = octetLine.to_ulong();
    int column = octetColumn.to_ulong();
    int S0 = SBox0[column][line];
    return res;
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
    vector<int> AEPxorK1 = xorK1(AEP, K1);

    vector<int> eOctet = uCharToOctet(e);
    vector<int> eIP = getIP(eOctet);
    vector<int> eEP = getEP(eIP);
    vector<int> eEPxorK1 = xorK1(eEP, K1);

    vector<int> AS0 = getS0(AEPxorK1);
    return 0;
}