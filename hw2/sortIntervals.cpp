//  sortIntervals.cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void mergeSort(int* a, int* b, int* c, int p, int r);
void merge(int* a, int* b, int* c, int p, int q, int r);

int main(){
    vector<int> v;
    int tok;
    while (cin >> tok){
        v.push_back(tok);
        if (cin.get()=='\n') {
            break;
        }
    }
    
    int n = (int)v.size()/2;
    
    int interval1[n];
    int interval2[n];
    int num[n];
    for (int i = 0; i < n; ++i) {
        interval1[i] = v[2*i];
        interval2[i] = v[2*i+1];
        num[i] = i+1;
    }
    
    mergeSort(interval1, interval2, num, 0, n-1);
    
    int i = 0, j;
    vector<int> eL,eR;
    while (i < n-1) {
        j = i + 1;
        if (interval1[i]==interval1[j]) {
            eL.push_back(i);
            while (interval1[i] == interval1[j] && j<n) {
                ++j;
            }
            eR.push_back(j-1);
        }
        i = j;
    }
    
    int e = (int)eL.size();
    for (int i = 0; i < e; ++i) {
        mergeSort(interval2, interval1, num, eL[i], eR[i]);
    }
    
    for (int i = 0; i < n; ++i){
        cout << interval1[i] << " " << interval2[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; ++i){
        cout << num[i] << " ";
    }
    cout << endl;
}

void mergeSort(int* a, int* b, int* c, int p, int r){
    if (p < r){
        int q = (p+r)/2;
        mergeSort(a, b, c, p, q);
        mergeSort(a, b, c, q+1, r);
        merge(a, b, c, p, q, r);
    }
}
void merge(int* a, int* b, int* c, int p, int q, int r){
    vector<int> aL, aR, bL, bR, cL, cR;
    for (int i = p; i <= q; ++i) {
        aL.push_back(a[i]);
        bL.push_back(b[i]);
        cL.push_back(c[i]);
    }
    for (int i = q+1; i <= r; ++i) {
        aR.push_back(a[i]);
        bR.push_back(b[i]);
        cR.push_back(c[i]);
    }
    aL.push_back(INT_MAX);
    aR.push_back(INT_MAX);
    bL.push_back(INT_MAX);
    bR.push_back(INT_MAX);
    cL.push_back(INT_MAX);
    cR.push_back(INT_MAX);
    
    int k, i, j;
    for (k = p, i = 0, j = 0; k <= r; ++k) {
        if (aL[i] <= aR[j]) {
            a[k] = aL[i];
            b[k] = bL[i];
            c[k] = cL[i];
            ++i;
        }
        else{
            a[k] = aR[j];
            b[k] = bR[j];
            c[k] = cR[j];
            ++j;
        }
    }
}
