#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

static double dmix(double x, double mean, double max, double min);

int main(){
    vector<double> data;
    double tok;
    while(cin >> tok){
        data.push_back(tok);
    }
    int t = (int)data.size();
    double min = data[0];
    double max = data[0];
    for (int i = 0; i < t; ++i) {
        if (data[i] > max) {
            max = data[i];
        }
        if (data[i] < min) {
            min = data[i];
        }
    }
    
    int a=0, b=0;
    a = floor(min);
    b = ceil(max);
    double llk = 0, maxllk = 0;
    int mu = 0;
    
    for (int j = 0; j < t; ++j) {
        llk += log(dmix(data[j], double(a), max, min));
    }
    maxllk = llk;
    mu = a;
    
    if (a == b) {
        cout << a << endl;
    }
    else{
        for (int i = a + 1; i < b + 1; ++i) {
            llk = 0;
            for (int j = 0; j < t; ++j) {
                llk += log(dmix(data[j], double(i), max, min));
            }
            if (llk > maxllk) {
                maxllk = llk;
                mu = i;
            }
        }
        cout << mu << endl;
    }
}
static double dmix(double x, double mean, double max, double min){
    return 0.5 / sqrt(2.0 * M_PI) * exp(- 0.5 * (x - mean) * (x - mean)) + 0.5 / (max - min);
}
