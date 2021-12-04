#ifndef SHIFTPOWERMETHOD_H_
#define SHIFTPOWERMETHOD_H_

#include "AbstractPowerMethod.h"

template <typename T> class ShiftPowerMethod : public AbstractPowerMethod<T>{
private:
    Eigen::Vector<T,-1> Multiply(const Eigen::Vector<T,-1> &x) override;
    T _shift = 0;
    T _return(T &lambda) override {return lambda + _shift;};

public:
    ShiftPowerMethod(const Eigen::Matrix<T, -1, -1> &A) : AbstractPowerMethod<T>(A) {}; // Constructor that just sets the matrix
    ShiftPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit, const Eigen::Vector<T, -1> &x, const double &shift); // Constructor that sets matrix, maxit, tol and shift
    ShiftPowerMethod(const std::map<std::string, std::any> &map); // Constructor that sets arguments from the map
    void SetShift(const T &shift) {_shift = shift;};
    // ~ShiftPowerMethod();
};
#endif //SHIFTPOWERMETHOD_H_
