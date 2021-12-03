#ifndef SHIFTPOWERMETHOD_H_
#define SHIFTPOWERMETHOD_H_

#include "AbstractPowerMethod.h"

template <typename T> class ShiftPowerMethod : public AbstractPowerMethod<T>{
private:
    Eigen::Matrix<T,-1,1> Multiply();

public:
    ShiftPowerMethod(Eigen::Matrix<T, -1, -1> &Mat); // Constructor that just sets the matrix
    ShiftPowerMethod(Eigen::Matrix<T, -1, -1> &Mat, double tol, double maxit, Eigen::Matrix<T,-1,1> &x, double shift); // Constructor that sets matrix, maxit and tol
    ShiftPowerMethod(std::map<std::string, std::any> &map); // Constructor that sets arguments from the map
    ~ShiftPowerMethod();
};
#endif //SHIFTPOWERMETHOD_H_
