#ifndef ABSTRACTEIGS_H_
#define ABSTRACTEIGS_H_

#include <Eigen/Dense>
#include <iostream>
#include <complex>
#include <vector>
#include <map>
#include <string>
#include <any>
#include <exception>

template <typename T> class AbstractEigs {
protected:
    Eigen::Matrix<T,-1,-1> _A;
    double _tol = 1e-8;
    int _maxit = 10000;

public:
    AbstractEigs(const Eigen::Matrix<T, -1, -1> &A); // Constructor that just sets the matrix
    AbstractEigs(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit); // Constructor that sets matrix, maxit and tol
    AbstractEigs(const std::map<std::string, std::any> &map); // Constructor that sets arguments from the map
    virtual void SetMatrix(const Eigen::Matrix<T, -1, -1> &A); // Sets the matrix
    void SetTol(const double &t);
    void SetMaxit(const int &i);
    virtual std::vector<std::complex<double>> ComputeEigs() = 0;
};


#endif //ABSTRACTEIGS_H_
