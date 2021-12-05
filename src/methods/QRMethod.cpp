#include "QRMethod.h"
template <typename T>
Eigen::Vector<std::complex<double>, -1> QRMethod<T>::ComputeEigs() {
    Eigen::HouseholderQR<Eigen::Matrix<T, -1, -1>> QR((this->_A).rows(), (this->_A).cols());
    Eigen::Matrix<T, -1, -1> A_k((this->_A).rows(), (this->_A).cols());
    Eigen::Matrix<T, -1, -1> A_next((this->_A).rows(), (this->_A).cols());
    // Needed for the first step
    A_next = this->_A;
    double res = (this->_tol + 1) * A_next.norm();
    int it = 0;
    while ((it < this->_maxit) && (res > this->_tol * A_next.norm())){
        A_k = A_next;
        QR = A_k.householderQr();
        A_next =  Eigen::Matrix<T, -1, -1>(QR.matrixQR().template triangularView<Eigen::Upper>()) * QR.householderQ();
        res = (A_k - A_next).norm();
    }
    if (it == this->_maxit){
        throw(std::runtime_error("Reached maximum number of iterations"));
    }
    Eigen::Vector<std::complex<double>, -1> eigs;
    // TO HANDLE THE CASE OF COMPLEX EIGENVALUES
    std::cout << A_next.diagonal(-1) << std::endl;
    eigs = A_next.diagonal();
    return eigs;
}

// Needed for linking
template class QRMethod<double>;
template class QRMethod<std::complex<double>>;

