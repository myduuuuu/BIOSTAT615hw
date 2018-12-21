#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

void fillVector(vector<int>& row, vector<int>& element, int rownumber, int n);
void fillVectVector(vector<vector<int> >& column, vector<int>& element, int n);
void calculation(vector<int>& irow, vector<vector<int> >& col, int n);

int main(){
    int k;
    cin >> k;
    int i;
    cin >> i;
    int j;
    cin >> j;
    vector<int> a;
    int integer;
    while (cin >> integer) {
        a.push_back(integer);
    }
    int n = (int)a.size();
    
    vector<int> irow;
    vector<vector<int> > col;
    
    fillVector(irow, a, i, n);
    fillVectVector(col, a, n);
    
    for (int power = 1; power < k; ++power) {
        calculation(irow, col, n);
    }
    
    int result = irow[j-1];
    
    int output[4];
    for (int i = 3; i >= 0; --i) {
        output[i] = result % 10;
        result /= 10;
    }
    
    int index;
    if ((output[0]==0) && (output[1]==0) && (output[2]==0) && (output[3]==0)) {
        cout << 0 << endl;
    }
    else{
        for (index = 0; index < 4; ++index) {
            if (output[index] != 0) {
                break;
            }
        }
        for (; index < 4; ++index) {
            cout << output[index];
        }
        cout << endl;
    }
}

void fillVector(vector<int>& row, vector<int>& element, int rownumber, int n){
    if (rownumber > 1) {
        for (int m = rownumber; m > 0; --m) {
            row.push_back(element[m-1]);
        }
        for (int m = 1; m < n - rownumber + 1; ++m) {
            row.push_back(element[m]);
        }
    }
    else{
        for (int m = 0; m < n; ++m) {
            row.push_back(element[m]);
        }
    }
}

void fillVectVector(vector<vector<int> >& column, vector<int>& element, int n){
    vector<int> tmp;
    for (int i = 1; i < n + 1 ; ++i) {
        fillVector(tmp, element, i, n);
        column.push_back(tmp);
        tmp.clear();
    }
}

void calculation(vector<int>& irow, vector<vector<int> >& col, int n){
    vector<int> irowtemp;
    for (int p = 0; p < n; ++p) {
        int entree = 0.0;
        for (int q = 0; q < n; ++q) {
            entree += irow[q]*col[p][q];
        }
        entree = entree - (entree/10000)*10000;
        irowtemp.push_back(entree);
    }
    irow.clear();
    for (int p = 0; p < n; ++p) {
        irow.push_back(irowtemp[p]);
    }
    irowtemp.clear();
}
