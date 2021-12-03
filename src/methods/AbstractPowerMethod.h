#ifndef ABSTRACTPOWERMETHOD_H_
#define ABSTRACTPOWERMETHOD_H_

#include "AbstractEigs.h"

template <typename T> class AbstractPowerMethod : public AbstractEigs<T>{
protected:
    Eigen::Matrix<T,-1,1> x0;       // Initial vector
    virtual Eigen::Matrix<T,-1,1> Multiply() = 0; // Does the multiplication step

public:
    AbstractPowerMethod(Eigen::Matrix<T, -1, -1> &Mat);
    AbstractPowerMethod(Eigen::Matrix<T, -1, -1> &Mat, double tol, double maxit, Eigen::Matrix<T,-1,1> &x);
    AbstractPowerMethod(std::map<std::string, std::any> &map);
    void SetInitVec(Eigen::Matrix<T,-1,1> &x);
    virtual std::vector<std::complex<double>> ComputeEigs();
};

#endif //ABSTRACTPOWERMETHOD_H_
