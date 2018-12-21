//  simpleLinearRegression.cpp
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<cmath>
#include<math.h>
using namespace std;

int main(int argc, char* argv[]){
    double n= 0.0;
    n = argc-1;
    double xbar = 1.0/n;
    double nominator = 0.0, denominator = 0.0;
    for (int i = 2; i <= n; i++){
        denominator += (i-1.0)/double(i)*(i/n-xbar)*(i/n-xbar);
        xbar += (i/n-xbar)/double(i);
    }
    
    double ybar = 0.0, s2 = 0.0;
    ybar = atof(argv[1]);
    for (int i = 2; i <= n; i++){
        s2 += (i-1.0)/double(i)*(atof(argv[i])-ybar);
        ybar += (atof(argv[i])-ybar)/i;
    }
    
    for (int i = 1; i <= n; i++){
        nominator += (i/n - xbar)*(atof(argv[i]) - ybar);
    }
    double slope, intercept;
    slope = nominator/denominator;
    intercept = ybar - slope*xbar;
    cout << setprecision(8)<<intercept<<" "<<slope<<endl;
}
