#ifndef SHIFTPOWERMETHOD_H_
#define SHIFTPOWERMETHOD_H_

#include "AbstractPowerMethod.h"

template <typename T> class ShiftPowerMethod : public AbstractPowerMethod<T>{
protected:
    T _shift = 0;

private:
    T _return(T &lambda) override {return lambda + _shift;};
    virtual Eigen::Vector<T,-1> Multiply(const Eigen::Vector<T,-1> &x) override;

public:
    ShiftPowerMethod(const Eigen::Matrix<T, -1, -1> &A) : AbstractPowerMethod<T>(A) {}; // Constructor that just sets the matrix
    ShiftPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit, const Eigen::Vector<T, -1> &x0, const T &shift); // Constructor that sets matrix, maxit, tol and shift
    ShiftPowerMethod(std::map<std::string, std::any> &map); // Constructor that sets arguments from the map
    void SetShift(const T &shift) {_shift = shift;};
    // ~ShiftPowerMethod();
};
#endif //SHIFTPOWERMETHOD_H_
