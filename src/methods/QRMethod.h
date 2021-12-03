#ifndef QRMETHOD_H
#define QRMETHOD_H

#include "AbstractEigs.h"

template <typename T> class QRMethod : public AbstractEigs<T>{
public:
    QRMethod(Eigen::Matrix<T, -1, -1> &Mat); // Constructor that just sets the matrix
    QRMethod(Eigen::Matrix<T, -1, -1> &Mat, double tol, double maxit); // Constructor that sets matrix, maxit and tol
    QRMethod(std::map<std::string, std::any> &map); // Constructor that sets arguments from the map
    virtual std::vector<std::complex<double>> ComputeEigs();
    ~QRMethod();
};

#endif //QRMETHOD_H_
