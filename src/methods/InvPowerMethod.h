#ifndef INVPOWERMETHOD_H_
#define INVPOWERMETHOD_H_

#include "AbstractPowerMethod.h"

template <typename T> class InvPowerMethod : public AbstractPowerMethod<T>{
public:
    InvPowerMethod(const Eigen::Matrix<T, -1, -1> &A) : AbstractPowerMethod<T>(A) {}; // Constructor that just sets the matrix
    InvPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit, const Eigen::Vector<T,-1> &x0) : AbstractPowerMethod<T>(A, tol, maxit, x0) {}; // Constructor that sets matrix, maxit and tol
    InvPowerMethod(std::map<std::string, std::any> &map) : AbstractPowerMethod<T>(map) {}; // Constructor that sets arguments from the map
    virtual ~InvPowerMethod() override {};
    virtual Eigen::Vector<std::complex<double>, -1> ComputeEigs() override;

private:
    Eigen::Vector<T,-1> Multiply(const Eigen::Vector<T,-1> &x) override;
    T _return(T &lambda) override {return (double(1) / lambda);};
    Eigen::FullPivLU<Eigen::Matrix<T, -1, -1>> _LU;
};

#endif //INVPOWERMETHOD_H_
