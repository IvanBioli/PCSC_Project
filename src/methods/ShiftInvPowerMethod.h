#ifndef SHIFTINVPOWERMETHOD_H_
#define SHIFTINVPOWERMETHOD_H_

#include "ShiftPowerMethod.h"

template <typename T> class ShiftInvPowerMethod : public ShiftPowerMethod<T> {
public:
    ShiftInvPowerMethod(const Eigen::Matrix<T, -1, -1> &A) : ShiftPowerMethod<T>(A) {}; // Constructor that just sets the matrix and computes the LU factorization
    ShiftInvPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit, const Eigen::Vector<T,-1> &x0, const T &shift) : ShiftPowerMethod<T>(A, tol, maxit, x0, shift) {}; // Constructor that sets matrix, maxit and tol
    ShiftInvPowerMethod(std::map<std::string, std::any> &map) : ShiftPowerMethod<T>(map) {}; // Constructor that sets arguments from the map
    // ~ShiftInvPowerMethod();
    Eigen::Vector<std::complex<double>, -1> ComputeEigs() override;

private:
    Eigen::FullPivLU<Eigen::Matrix<T, -1, -1>> _LU;
    Eigen::Vector<T,-1> Multiply(const Eigen::Vector<T,-1> &x) override;
    T _return(T &lambda) override {return (double(1) / lambda + this->_shift);};
};

#endif //SHIFTINVPOWERMETHOD_H_
