#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
#include <cfloat>
#include <algorithm>

using namespace std;

void mergeSort(vector<pair<double,int> >& A, int p, int r);
void merge(vector<pair<double,int> >& A, int p, int q, int r);

int main(int argc, char* argv[]){
    vector<pair<double,int> > p;
    double pvalue;
    int index = 1;
    while (cin >> pvalue) {
        p.push_back(pair<double,int>(pvalue, index));
        ++index;
    }
    
    int m = (int)p.size();
    mergeSort(p, 0, m-1);
    
    double alpha = atof(argv[1]);
    double q_denominator = 0.0;
    for (int j = 1; j < m + 1; ++j) {
        q_denominator += (1.0/double(j));
    }
    double q = 0.0;
    q = alpha/q_denominator;
    
    int k = 0;
    for (int i = 1; i < m+1; ++i) {
        if (p[i-1].first <= q*((double)(i)/(double)m)) {
            k = max(k, i);
        }
    }
    
    if (k) {
        for (int i = 0; i < k; ++i) {
            cout << p[i].second << " ";
        }
        cout << endl;
    }
    else{
        cout << 0 << endl;
    }
}

void mergeSort(vector<pair<double,int> >& A, int p, int r){
    if (p < r) {
        int q = (p+r)/2;
        mergeSort(A, p, q);
        mergeSort(A, q+1, r);
        merge(A, p, q, r);
    }
}

void merge(vector<pair<double,int> >& A, int p, int q, int r){
    vector<pair<double, int> > aL, aR;
    for (int i=p; i <= q; ++i) {
        aL.push_back(A[i]);
    }
    for (int i=q+1; i <= r; ++i) {
        aR.push_back(A[i]);
    }
    aL.push_back(pair<double, int>(__DBL_MAX__, INT_MAX));
    aR.push_back(pair<double, int>(__DBL_MAX__, INT_MAX));
    for (int k=p, i=0, j=0; k <= r; ++k) {
        if (aL[i].first <= aR[j].first) {
            A[k] = aL[i];
            ++i;
        }
        else{
            A[k] = aR[j];
            ++j;
        }
    }
}
