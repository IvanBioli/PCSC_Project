#ifndef INVPOWERMETHOD_H_
#define INVPOWERMETHOD_H_

#include "AbstractPowerMethod.h"

template <typename T> class InvPowerMethod : public AbstractPowerMethod<T>{
public:
    // TO DISCUSS: WE DO NOT NEED TO STORE A, WE JUST NEED THE LU FACTORIZATION OF A
    InvPowerMethod(const Eigen::Matrix<T, -1, -1> &A) : AbstractPowerMethod<T>(A) {}; // Constructor that just sets the matrix and computes the LU factorization
    InvPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit, const Eigen::Vector<T,-1> &x0) : AbstractPowerMethod<T>(A, tol, maxit, x0) {}; // Constructor that sets matrix, maxit and tol
    InvPowerMethod(std::map<std::string, std::any> &map) : AbstractPowerMethod<T>(map) {}; // Constructor that sets arguments from the map
    // ~InvPowerMethod();
    virtual Eigen::Vector<std::complex<double>, -1> ComputeEigs() override;

private:
    Eigen::Vector<T,-1> Multiply(const Eigen::Vector<T,-1> &x) override;
    T _return(T &lambda) override {return (double(1) / lambda);};

protected:
    Eigen::FullPivLU<Eigen::Matrix<T, -1, -1>> _LU;
};

#endif //INVPOWERMETHOD_H_
