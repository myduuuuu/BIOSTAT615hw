//  sort.cpp
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <math.h>
using namespace std;

int main(int argc, char* argv[]){
    int p;
    p = argc-1;
    double x[p];
    for (int i = 0; i < p; i++){
        x[i] = atof(argv[i+1]);
    }
    
    double exponent[5], pr[5];
    for (int k = 1; k <= 5; k++){
        exponent[k-1] = pow(2.0, -k);
        for (int j = 1; j <= p; j++) {
            exponent[k-1] += pow(2.0, abs(k-j))*x[j-1];
        }
    }
    
    double tem[5];
    for (int i = 0; i < 5; i++){
        tem[i] = exponent[i];
    }
    
    double exmax = 0.0, key = 0.0;
    for (int j = 1; j < 5; ++j) {
        key = tem[j];
        int i = j - 1;
        while ((i>=0)&&(tem[i]>key)) {
            tem[i+1] = tem[i];
            --i;
        }
        tem[i+1]=key;
    }
    exmax = tem[4];
    
    for (int i = 0; i < 5; i++) {
        exponent[i] -= exmax;
    }
    
    for (int i = 0; i < 5; i++) {
        pr[i] = exp(exponent[i])/(exp(exponent[0])+exp(exponent[1])+exp(exponent[2])+exp(exponent[3])+exp(exponent[4]));
    }
    for (int i = 0; i < 5; i++){
        cout << setprecision(8) << pr[i] << endl;
    }
}
