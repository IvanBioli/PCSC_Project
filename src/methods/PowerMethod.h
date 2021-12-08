#ifndef POWERMETHOD_H_
#define POWERMETHOD_H_

#include "AbstractPowerMethod.h"

template <typename T> class PowerMethod : public AbstractPowerMethod<T>{
public:
    PowerMethod(const Eigen::Matrix<T, -1, -1> &A) : AbstractPowerMethod<T>(A) {}; // Constructor that just sets the matrix
    PowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit, const Eigen::Vector<T,-1> &x0) : AbstractPowerMethod<T>(A, tol, maxit, x0) {}; // Constructor that sets matrix, maxit and tol
    PowerMethod(std::map<std::string, std::any> &map) : AbstractPowerMethod<T>(map) {}; // Constructor that sets arguments from the map
    //~PowerMethod();

private:
    Eigen::Vector<T,-1> Multiply(const Eigen::Vector<T,-1> &x) override;
};

#endif //POWERMETHOD_H_
