//  momentStats.cpp
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<cmath>
#include<math.h>
using namespace std;
int main(int argc, char* argv[]){
    int n;
    n = argc-1;
    double x[n], mean = 0.0, var = 0.0, skew = 0.0, kurt = 0.0;
    for (int i = 0; i < n; i++){
        x[i] = atof(argv[i+1]);
    }
    //Calculate mean
    for (int j = 0; j < n; j++){
        mean += x[j];
    }
    mean /= n;
    //Calculate variance
    for (int k = 0; k < n; k++){
        var += pow((x[k] - mean),2);
    }
    var /= (n-1);
    cout << setprecision(8) << mean << endl;
    cout << setprecision(8) << var << endl;
    
    //Calculate skewness
    if (var != 0){
        for (int l = 0; l < n; l++){
            skew += pow(((x[l] - mean)/sqrt(var)),3);
        }
        skew /= n;
    //Calculate kurtosis
        for (int m = 0; m < n; m++){
            kurt += pow(((x[m] - mean)/sqrt(var)),4);
        }
        kurt /= n;
        kurt -= 3.0;
    
        cout << setprecision(8) << skew << endl;
        cout << setprecision(8) << kurt << endl;
    }
    return 0;
}
