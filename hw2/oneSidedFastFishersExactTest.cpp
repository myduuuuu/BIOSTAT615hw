//  oneSidedFastFishersExactTest.cpp
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;

void initLogFacs(double* logFacs, int n);
double logHypergeometricProb(double* logFacs, int a, int b, int c, int d);

int main(int argc, char** argv){
    int a = atoi(argv[1]), b = atoi(argv[2]), c = atoi(argv[3]), d = atoi(argv[4]);
    int n = a + b + c + d;
    double* logFacs = new double[n+1];
    initLogFacs(logFacs, n);
    double logpCutoff = logHypergeometricProb(logFacs,a,b,c,d);
    double pFraction = 0;
    for (int x = 0; x <= a; ++x) {
        if (x >= max(a-d, 0)) {
            double I = logHypergeometricProb(logFacs, x, a+b-x, a+c-x, d-a+x);
            pFraction += exp(I - logpCutoff);
        }
    }
    double logpValue = logpCutoff + log(pFraction);
    if (exp(logpValue) < 0.05){
        cout << "significant" << endl;
    }
    else{
        cout << "not significant" << endl;
    }
    delete [] logFacs;
    return 0;
}

void initLogFacs(double* logFacs, int n){
    logFacs[0] = 0;
    for (int i = 1; i < n+1; ++i) {
        logFacs[i] = logFacs[i-1] + log((double)i);
    }
}
double logHypergeometricProb(double* logFacs, int a, int b, int c, int d){
    return logFacs[a+b] + logFacs[c+d] + logFacs[a+c] + logFacs[b+d] - logFacs[a] - logFacs[b] - logFacs[c] - logFacs[d] - logFacs[a+b+c+d];
}
