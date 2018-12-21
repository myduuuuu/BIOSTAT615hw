#include <iostream>
#include <Eigen/Dense>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "ReadMatrix615.h"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]){
    MatrixXd X = readFromFile<double>(argv[1]);
    MatrixXd Y = readFromFile<double>(argv[2]);
    double lambda = atof(argv[3]);
    JacobiSVD<MatrixXd> svd_X(X,ComputeThinU | ComputeThinV);
    MatrixXd singular = svd_X.singularValues();
    MatrixXd D = singular.array()/(singular.array() * singular.array() + lambda);
    MatrixXd reg = svd_X.matrixV() * D.asDiagonal() * svd_X.matrixU().transpose() * Y;
    VectorXd beta = reg.array().round();
    int n = (int)beta.size();
    for (int i = 0; i < n; ++i) {
        if (beta[i] != 0) {
            cout << i+1 << " " << beta[i] << endl;
        }
    }
    return 0;
}
