#include <iostream>
#include <cstdlib>
#include <vector>
#include <Eigen/Dense>
#include <iomanip>
#include "ReadMatrix615.h"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]){
    MatrixXd train_dat = readFromFile<double>(argv[1]);
    MatrixXd test_dat = readFromFile<double>(argv[2]);
    //cout << train_dat << endl;
    int train_rows=0, train_cols=0, test_rows=0, test_cols=0;
    train_rows = train_dat.rows();
    train_cols = train_dat.cols();
    test_rows = test_dat.rows();
    test_cols = test_dat.cols();
    //cout << train_rows << train_cols << test_rows << test_cols << endl;
    MatrixXd center_1(1, train_cols-1);
    MatrixXd center_0(1, train_cols-1);
    MatrixXd s_1(1, train_cols-1);
    MatrixXd s_0(1, train_cols-1);
    
    // id = (train_dat[ , 1] == 1)
    vector<int> v1;
    vector<int> v0;
    for (int i = 0; i < train_rows; ++i) {
        if (train_dat(i,0)==1) {
            v1.push_back(i);
        }
        else{
            v0.push_back(i);
        }
    }
    
    // construct center_1, center_0, s_1, s_0 (west algorithm)
    int id1 = 0;
    int id0 = 0;
    id1 = (int)v1.size();
    id0 = (int)v0.size();
    
    for (int j = 0; j < train_cols-1; ++j) {
        center_1(0,j) = train_dat(v1[0],j+1);
    }
    for (int j = 0; j < train_cols-1; ++j) {
        center_0(0,j) = train_dat(v0[0],j+1);
    }
    for (int j = 0; j < train_cols-1; ++j) {
        s_1(0,j) = 0.0;
    }
    for (int j = 0; j < train_cols-1; ++j) {
        s_0(0,j) = 0.0;
    }
    //cout << center_1 << endl << center_0 << endl;
    
    if (id1 > 1) {
        for (int i = 2; i <= id1; ++i) {
            for (int j = 1; j < train_cols; ++j) {
                s_1(0,j-1) += ((double(i)-1.0)/double(i)*(train_dat(v1[i-1],j)-center_1(0,j-1))*(train_dat(v1[i-1],j)-center_1(0,j-1)));
                center_1(0,j-1) += (train_dat(v1[i-1],j)-center_1(0,j-1))/double(i);
            }
        }
        s_1 = (1.0/((double)(id1)-1.0))*s_1;
    }
    
    if (id0 > 1) {
        for (int i = 2; i <= id0; ++i) {
            for (int j = 1; j < train_cols; ++j) {
                s_0(0,j-1) += (((double(i)-1.0)/double(i))*(train_dat(v0[i-1],j)-center_0(0,j-1))*(train_dat(v0[i-1],j)-center_0(0,j-1)));
                center_0(0,j-1) += (train_dat(v0[i-1],j)-center_0(0,j-1))/double(i);
                //cout << s_0 << endl << center_0 << endl;
                //cout << endl;
            }
        }
        s_0 = (1.0/((double)(id0)-1.0))*s_0;
    }
    //cout << center_1 << endl << center_0 << endl;
    //cout << s_1 << endl << s_0 << endl;
    
    //dist_1 = apply((test_dat[ , -1]-ones%*%center_1)^2/(ones%*%s_1), 1, sum)
    MatrixXd test(test_rows, test_cols-1);
    for (int i = 0; i < test_rows; ++i) {
        for (int j = 0; j < test_cols-1; ++j) {
            test(i,j) = (test_dat(i, j+1)-center_1(0,j))*(test_dat(i, j+1)-center_1(0,j))/s_1(0,j);
        }
    }
    //cout << test << endl;
    VectorXd dist_1(test_rows);
    dist_1 = test.rowwise().sum();
    //cout << dist_1 << endl;
    
    //dist_2
    for (int i = 0; i < test_rows; ++i) {
        for (int j = 0; j < test_cols-1; ++j) {
            test(i,j) = (test_dat(i, j+1)-center_0(0,j))*(test_dat(i, j+1)-center_0(0,j))/s_0(0,j);
        }
    }
    //cout << test << endl;
    VectorXd dist_0(test_rows);
    dist_0 = test.rowwise().sum();
    //cout << dist_0 << endl;
    
    // y_pred = as.numeric(dist_1 < dist_0)
    VectorXd y_pred(test_rows);
    for (int i = 0; i < test_rows; ++i) {
        if (dist_1[i] < dist_0[i]) {
            y_pred[i] = 1;
        }
        else{
            y_pred[i] = 0;
        }
    }
    //cout << y_pred << endl << endl;
    for (int i = 0; i < test_rows; ++i) {
        if (test_dat(i, 0) == y_pred[i]) {
            y_pred[i] = 1;
        }
        else{
            y_pred[i] = 0;
        }
    }
    double accuracy;
    accuracy = y_pred.mean();
    cout << setprecision(4) << accuracy << endl;
}
