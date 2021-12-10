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
    while ((it < this->_maxit) && (res > this->_tol * A_next.diagonal().norm())){
        A_k = A_next;
        QR = A_k.householderQr();
        A_next =  Eigen::Matrix<T, -1, -1>(QR.matrixQR().template triangularView<Eigen::Upper>()) * QR.householderQ();
        res = (A_k.diagonal() - A_next.diagonal()).norm();
        it = it + 1;
    }
    if (it == this->_maxit){
        throw(ConvergenceError("Reached maximum number of iterations"));
    }
    Eigen::Vector<std::complex<double>, -1> eigs;
    // TODO: HANDLE THE CASE OF COMPLEX EIGENVALUES
    eigs = A_next.diagonal();
    return eigs;
}

// Needed for linking
template class QRMethod<double>;
