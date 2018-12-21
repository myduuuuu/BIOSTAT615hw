#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <Eigen/Dense>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>


using namespace std;
using namespace boost;
using namespace Eigen;

int main(int argc, char** argv){
    double p = atof(argv[1]);
    double rho = atof(argv[2]);
    //create covariance matrix
    Matrix<double, Dynamic, Dynamic> matrix;
    matrix.resize(p,p);
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < p; ++j) {
            matrix(i,j) = exp(p*log(rho)*pow(abs(double(i-j)/p), 1.99)-abs(cos(double(i)/p))-abs(cos(double(j)/p)));
        }
    }
    //Cholesky decomposition, s.t. matrix = A*A.transpose
    LLT<MatrixXd> cholX(matrix);
    Matrix<double, Dynamic, Dynamic> A;
    A = cholX.matrixL();
    //find seed rng and set the function of normal distribution
    boost::random::mt19937 rng;
    normal_distribution<> norm(0,1);
    
    VectorXd z,X;
    z.resize(p);
    X.resize(p);
    double max, sum, prob;
    
    //Sampling X = A*z + 0 ~ N(0, AA') = N(0,matrix)
      //sample z~N(0,In) from standard normal distribution
      //draw one million random samples from MVN
    for (long j = 1; j <= 1000000; ++j) {
        //sample z~N(0,In) from standard normal distribution
        for (int i = 0; i < p; ++i) {
            z(i)=norm(rng);
        }
        //create X
        X = A*z;
        //calculate results (West Algorithm)
        max = max + (X.maxCoeff() - max)/double(j);
        sum = sum + (sqrt(X.cwiseProduct(X).sum()) - sum)/double(j);
        if (X(0)*X(1) > 0.5*rho) {
            prob++;
        }
    }
    //output the result with one valid precision digit
    cout << setprecision(1) << max << endl;
    cout << setprecision(1) << sum << endl;
    cout << setprecision(1) << prob/1000000 << endl;
}
