#include <iostream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/beta_distribution.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <ctime>
#include <vector>
#include <iomanip>

using namespace std;
using namespace boost;

void quickSort(vector<double>& A, int p, int r);

int main(int argc, char** argv){
    boost::random::mt19937 rng;
    if(argc > 1){
        rng.seed(atoi(argv[1]));
    }
    else{
        rng.seed(std::time(0));
    }
    uniform_real<> unif(0,1);
    boost::random::beta_distribution<> beta(atof(argv[1]), atof(argv[2]));
    int count;
    int accept = 0;
    double x, u, r;
    vector<double> sample;
    for (count = 0; accept < 5000000; count++) {
        x = beta(rng);
        u = unif(rng);
        r = exp(-x*x);
        if (u < r) {
            accept++;
            sample.push_back(x);
        }
    }
    double rate = 0.0;
    rate = 5000000/double(count);
    
    quickSort(sample, 0, sample.size()-1);
    
    int n = 5000000;
    cout << setprecision(1) << rate << endl;
    cout << setprecision(1) << sample[n*0.01-1] << " "
    << sample[n*0.25-1] << " " << sample[n*0.50-1] << " "
    << sample[n*0.75-1] << " " << sample[n*0.99-1] << endl;
    
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
