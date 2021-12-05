#ifndef QRMETHOD_H
#define QRMETHOD_H

#include "AbstractEigs.h"
// #include "Eigen/QR"

template <typename T> class QRMethod : public AbstractEigs<T>{
public:
    QRMethod(const Eigen::Matrix<T, -1, -1> &A) : AbstractEigs<T>(A) {}; // Constructor that just sets the matrix
    QRMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const double &maxit) : AbstractEigs<T>(A, tol, maxit) {}; // Constructor that sets matrix, maxit and tol
    QRMethod(std::map<std::string, std::any> &map) : AbstractEigs<T>(map) {}; // Constructor that sets arguments from the map
    virtual Eigen::Vector<std::complex<double>, -1> ComputeEigs();
    // ~QRMethod();
};

#endif //QRMETHOD_H_
