#include <iostream>

using namespace std;

bool* padding(bool *msg, int l);

int main() {
    bool msg[] = {0, 1, 0, 1};
    bool *f1 = padding(msg, sizeof(msg) / sizeof(bool));
    cout << f1;
    return 0;
}

bool* padding(bool *msg, int l){ // l + 1 + (0...0) = 512*k + 448
    int numOf0;
    int k;
    if((l+1)%512 <= 448)
    {
        numOf0 = (l+1)%512 - 448;
        k = (l+1)/512;
    }
    else
    {
        numOf0 = (512-(l+1)%512) + 448;
        k = (l+1)/512 + 1;
    }
    bool paddedMsg[l + 1 + numOf0];
    for(int i = 0; i < l; i ++) paddedMsg[i] = msg[i];
    paddedMsg[l] = 1;
    for(int i = 0; i < numOf0; i++){
        paddedMsg[l+1+i] = 0;
    }

    return paddedMsg;
}

