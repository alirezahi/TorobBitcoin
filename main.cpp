#include <iostream>

using namespace std;

bool* padding(bool *msg, int l);
int SIZE_OF_BLOCK = 2;
bool** parsing(bool*,int);
void printSth(bool**);


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

void printSth(bool** data,int n,int m){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout << data[i][j];
        }
        cout << endl;
    }
}

bool** parsing(bool* data,int data_size){
    int number_of_blocks = (int)(data_size/SIZE_OF_BLOCK);
    bool **blocks = new bool*[number_of_blocks];
    for(int i = 0; i < data_size ;i++){
        if(i % SIZE_OF_BLOCK == 0){
            blocks[(int)(i/SIZE_OF_BLOCK)] = new bool[SIZE_OF_BLOCK];
        }
        blocks[(int)(i/SIZE_OF_BLOCK)][i%SIZE_OF_BLOCK] = data[i];
    }
    printSth(blocks,2,2);
}
