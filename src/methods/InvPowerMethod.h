#ifndef INVPOWERMETHOD_H_
#define INVPOWERMETHOD_H_

#include "AbstractPowerMethod.h"

template <typename T> class InvPowerMethod : public AbstractPowerMethod<T>{
public:
    InvPowerMethod(Eigen::Matrix<T, -1, -1> &Mat); // Constructor that just sets the matrix
    InvPowerMethod(Eigen::Matrix<T, -1, -1> &Mat, double tol, double maxit, Eigen::Matrix<T,-1,1> &x); // Constructor that sets matrix, maxit and tol
    InvPowerMethod(std::map<std::string, std::any> &map); // Constructor that sets arguments from the map
    ~InvPowerMethod();

private:
    // FACTORIZATION
    Eigen::Matrix<T,-1,1> Multiply();
};

#endif //INVPOWERMETHOD_H_
