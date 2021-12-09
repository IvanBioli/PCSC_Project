#ifndef ABSTRACTPOWERMETHOD_H_
#define ABSTRACTPOWERMETHOD_H_

#include "AbstractEigs.h"

template <typename T> class AbstractPowerMethod : public AbstractEigs<T>{
protected:
    Eigen::Vector<T,-1> _x0;       // Initial vector
    virtual Eigen::Vector<T,-1> Multiply(const Eigen::Vector<T,-1> &x) = 0; // Does the multiplication step
    virtual T _return(T &lambda) {return lambda;};

public:
    AbstractPowerMethod(const Eigen::Matrix<T, -1, -1> &A);
    AbstractPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int maxit, const Eigen::Matrix<T,-1,1> &x0);
    AbstractPowerMethod(std::map<std::string, std::any> &map);
    virtual ~AbstractPowerMethod() override {};
    void SetInitVec(const Eigen::Matrix<T,-1,1> &x0);
    Eigen::Vector<T,-1> GetInitVec() {return _x0;};
    virtual Eigen::Vector<std::complex<double>, -1> ComputeEigs() override;
};

#endif //ABSTRACTPOWERMETHOD_H_
