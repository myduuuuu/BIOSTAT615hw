//  simpleQuantiles.cpp
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

void quickSort(vector<double>& A, int p, int r);

int main(int argc, char* argv[]){
    vector<double> v;
    double tok;
    while (cin >> tok){
        v.push_back(tok);
        if (cin.get()=='\n') {
            break;
        }
    }
    
    quickSort(v, 0, (int)v.size()-1);
    
    double n = v.size();

    for (int i = 1; i <= argc-1; i++) {
        if (atof(argv[i])==0.0){
            cout << v[0] << " ";
        }
        else if (atof(argv[i])==1.0) {
            cout << v[n-1] << " ";
        }
        else if (n*atof(argv[i]) == floor(n*atof(argv[i]))) {
            cout << v[n*atof(argv[i])-1] << " ";
        }
        else{
            cout << v[floor(n*atof(argv[i]))] << " ";
        }
    }
    cout << endl;
}

void quickSort(vector<double>& A, int p, int r){
    if (p < r) {
        double piv = A[r];
        int i = p-1;
        double tmp;
        for (int j = p; j < r; ++j) {
            if (A[j] < piv) {
                ++i;
                tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
        }
        A[r] = A[i+1];
        A[i+1] = piv;
        quickSort(A, p, i);
        quickSort(A, i+2, r);
    }
}
