#ifndef SHIFTINVPOWERMETHOD_H_
#define SHIFTINVPOWERMETHOD_H_

#include "InvPowerMethod.h"

template <typename T> class ShiftInvPowerMethod : public InvPowerMethod<T>{
public:
    ShiftInvPowerMethod(const Eigen::Matrix<T, -1, -1> &A) : InvPowerMethod<T>(A) {}; // Constructor that just sets the matrix and computes the LU factorization
    ShiftInvPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit, const Eigen::Vector<T,-1> &x0, const T &shift) : InvPowerMethod<T>(A, tol, maxit, x0) {_shift = shift;}; // Constructor that sets matrix, maxit and tol
    ShiftInvPowerMethod(std::map<std::string, std::any> &map); // Constructor that sets arguments from the map
    // ~InvPowerMethod();
    Eigen::Vector<std::complex<double>, -1> ComputeEigs() override;
    void SetShift(const T &shift) {_shift = shift;};

private:
    T _shift = 0;
    T _return(T &lambda) override {return (double(1) / lambda + _shift);};};

#endif //SHIFTINVPOWERMETHOD_H_
