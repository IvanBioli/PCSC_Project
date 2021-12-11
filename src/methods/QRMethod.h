#ifndef QRMETHOD_H
#define QRMETHOD_H

#include "AbstractEigs.h"

template <typename T> class QRMethod : public AbstractEigs<T>{
public:
    /**
     * @copydoc AbstractEigs::AbstractEigs(const Eigen::Matrix<T, -1, -1> &A)
     */
    QRMethod(const Eigen::Matrix<T, -1, -1> &A) : AbstractEigs<T>(A) {};

    /**
     * @copydoc AbstractEigs::AbstractEigs(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit)
     */
    QRMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const double &maxit) : AbstractEigs<T>(A, tol, maxit) {};

    /**
     * @copydoc  AbstractEigs::AbstractEigs(std::map<std::string, std::any> &map)
     */
    QRMethod(std::map<std::string, std::any> &map) : AbstractEigs<T>(map) {};

    // Destructor
    virtual ~QRMethod() override {};

    /**
     * @brief Returns the eigenvalues computed using the QR method.
     * @return Vector of complex numbers containing the eigenvalues computed using the QR method.
     */
    virtual Eigen::Vector<std::complex<double>, -1> ComputeEigs();
};

#endif //QRMETHOD_H_
