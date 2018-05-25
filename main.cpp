#include <iostream>

using namespace std;

bool* padding(bool *msg, int l);
int SIZE_OF_BLOCK = 2;
bool** parsing(bool*,int);
bool** parsing_w(bool*,int);
void printSth(bool**);

bool* rot(bool*,int);
bool* shf(bool*,int);
bool* xor_array(bool*,bool*,int);


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
    return blocks;
}

bool* rot(bool* data,int size){
    bool * rot_data = new bool[size];
    rot_data[0]=data[size-1];
    for(int i = 1;i < size;i++){
        rot_data[i] = data[i-1];
    }
    return rot_data;
}

bool* shf(bool* data,int size){
    bool * shf_data = new bool[size];
    for(int i = 1;i < size;i++){
        shf_data[i] = data[i-1];
    }
    shf_data[0]=0;
    return shf_data;
}

bool* xor_array(bool* first_bool_array,bool* second_bool_array, int size){
    bool* xor_data = new bool[size];
    for(int i = 0; i < size; i++){
        xor_data[i] = first_bool_array[i]^second_bool_array[i];
    }
    return xor_data;
}

bool* sigma(bool* data,int size,int first_rot_loop,int second_rot_loop,int shf_loop){
    bool* rot_first_result=data;
    for(int i = 0;i < first_rot_loop; i++){
        rot_first_result = rot(rot_first_result,size);
    }
    bool* rot_second_result=data;
    for(int i = 0;i < second_rot_loop; i++){
        rot_second_result = rot(rot_second_result,size);
    }
    bool* shf_result=data;
    for(int i = 0;i < shf_loop; i++){
        shf_result = shf(shf_result,size);
    }
    return xor_array(xor_array(rot_first_result,rot_second_result,size),shf_result,size);
}

bool* sum_array(bool* first_bool_array,bool* second_bool_array, int size){
    bool* sum_data = new bool[size];
    bool* carry_array = new bool[size+1];
    for(int i = 0; i < size; i++){
        carry_array[i] = 0;
    }
    for(int i = 0; i < size; i++){
        sum_data[i] = first_bool_array[i]+second_bool_array[i]+carry_array[i];
        if(first_bool_array[i] == 1 && second_bool_array[i] == 1){
            carry_array[i+1] = 1;
        }
    }
    return sum_data;
}

bool* sigma_zero(bool* data,int size){
    return sigma(data,size,17,14,12);
}

bool* sigma_one(bool* data,int size){
    return sigma(data,size,9,19,9);
}

bool** parsing_w(bool* data,int data_size){
    bool ** w_blocks = new bool*[64];
    for(int i = 0;i < data_size;i++){
        if(i % 32 == 0){
            w_blocks[i/32] = new bool[32];
        }
        w_blocks[i/32][i%32] = data[i];
    }
    for(int i=16; i < 64; i++){
        w_blocks[i] = sum_array(
                sum_array(
                        sigma_one(w_blocks[i-1],32),
                        w_blocks[i-6],
                        32
                ),
                sum_array(
                        sigma_zero(w_blocks[i-12],32),
                        w_blocks[i-15],
                        32
                ),
                32
        );
    }
    return w_blocks;

}

bool** permutation(bool** data){
    bool** permutation_data = new bool*[64];
    for(int i = 0; i < 64; i++){
        permutation_data = new bool[32];
        for(int j = 0; j < 32; j++){
            int current_block = 3-(j/8);
            permutation_data[i][current_block*8 + (7-j%8)] = data[i][j];
        }
    }
    return permutation_data;
}

