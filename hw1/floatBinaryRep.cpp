//  floatBinaryRep.cpp
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <math.h>
using namespace std;

int main(int argc, char* argv[]){
    float num;
    num = atof(argv[1]);
    
    int binary[32], accuracy = 0;
    if (num < 0){
        binary[0] = 1;
    }
    else{
        binary[0] = 0;
    }
    
    if (num != 0){
        int exponent = 0, tem1 = 0;
        exponent = floor(log2(abs(num)))+127;
        float significand, tem2;
        significand = abs(num)/pow(2, exponent-127) - 1;
        tem1 = exponent;
        tem2 = significand;
        
        int remain[8] = {};
        for (int i = 0; i < 8; i++){
            remain[i] = exponent % 2;
            exponent /= 2;
        }
        for (int j = 1; j < 9; j++){
            binary[j] = remain[8-j];
        }
        
        int c = 0;
        for (int j = 9; j < 32; j++) {
            significand = significand * 2;
            c = significand;
            significand = significand - c;
            binary[j] = c;
        }
        
        float decimal = 0.0;
        for (int j = 9; j < 32; j++) {
            decimal += binary[j]*pow(2, 8-j);
        }
        float ex = 0.0;
        for (int j = 1; j < 9; j++) {
            ex += binary[j]*pow(2, 8-j);
        }
        ex -= 127;
        float cal = 0.0;
        cal = pow(-1, binary[0])*(1+decimal)*pow(2,ex);
        
        if (cal == atof(argv[1])){
            accuracy = 1;
        }
    }
    else{
        for (int i = 0; i < 32; i++){
            binary[i] = 0;
        }
        accuracy = 1;
    }
    
    for (int i = 0; i < 32; i++) {
        cout << binary[i];
    }
    cout << endl << accuracy << endl;
}
