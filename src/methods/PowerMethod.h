#ifndef POWERMETHOD_H_
#define POWERMETHOD_H_

#include "AbstractPowerMethod.h"

template <typename T> class PowerMethod : public AbstractPowerMethod<T>{
public:
    PowerMethod(Eigen::Matrix<T, -1, -1> &Mat); // Constructor that just sets the matrix
    PowerMethod(Eigen::Matrix<T, -1, -1> &Mat, double tol, double maxit, Eigen::Matrix<T,-1,1> &x); // Constructor that sets matrix, maxit and tol
    PowerMethod(std::map<std::string, std::any> &map); // Constructor that sets arguments from the map
    ~PowerMethod();

private:
    Eigen::Matrix<T,-1,1> Multiply();
};

#endif //POWERMETHOD_H_
