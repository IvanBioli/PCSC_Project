#ifndef ABSTRACTEIGS_H_
#define ABSTRACTEIGS_H_

#include <Eigen/Dense>
#include <iostream>
#include <complex>
#include <vector>
#include <map>
#include <string>
#include <any>

template <typename T> class AbstractEigs {
protected:
    Eigen::Matrix<T,-1,-1> A;
    double tol;
    int maxit;

public:
    AbstractEigs(Eigen::Matrix<T, -1, -1> &Mat); // Constructor that just sets the matrix
    AbstractEigs(Eigen::Matrix<T, -1, -1> &Mat, double tol, double maxit); // Constructor that sets matrix, maxit and tol
    AbstractEigs(std::map<std::string, std::any> &map); // Constructor that sets arguments from the map
    void SetMatrix(Eigen::Matrix<T, -1, -1> &Mat); // Sets the matrix
    void SetTol(double &t);
    void SetMaxit(int &i);
    virtual std::vector<std::complex<double>> ComputeEigs() = 0;
};


#endif //ABSTRACTEIGS_H_
