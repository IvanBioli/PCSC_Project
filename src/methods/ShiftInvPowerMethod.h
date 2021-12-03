#ifndef SHIFTINVPOWERMETHOD_H_
#define SHIFTINVPOWERMETHOD_H_

#include "InvPowerMethod.h"

template <typename T> class ShiftInvPowerMethod : public InvPowerMethod<T>{
private:
    Eigen::Matrix<T,-1,1> Multiply();

public:
    ShiftInvPowerMethod(Eigen::Matrix<T, -1, -1> &Mat); // Constructor that just sets the matrix
    ShiftInvPowerMethod(Eigen::Matrix<T, -1, -1> &Mat, double tol, double maxit, Eigen::Matrix<T,-1,1> &x, double shift); // Constructor that sets matrix, maxit and tol
    ShiftInvPowerMethod(std::map<std::string, std::any> &map); // Constructor that sets arguments from the map
    ~ShiftInvPowerMethod();
};

#endif //SHIFTINVPOWERMETHOD_H_
