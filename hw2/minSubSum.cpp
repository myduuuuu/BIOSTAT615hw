//  minSubSum.cpp
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

int main(int argc, char* argv[]){
    int mini = 0;
    int cur = 0;
    vector<int> A;
    int num;
    while (cin >> num) {
        A.push_back(num);
        if (cin.get()=='\n') {
            break;
        }
    }
    int n = (int)A.size();
    
    for (int i = 0; i < n; i++) {
        cur += A[i];
        if (cur > 0) {
            cur = 0;
        }
        if (cur < mini) {
            mini = cur;
        }
    }
    cout << mini << endl;
}
