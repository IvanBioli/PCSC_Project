#include "QRMethod.h"

/**
 * @details Computes the eigenvalues following the QR algorithm.
 *
 * If the maximum number of iterations is reached it throws an error or type ConvergenceError with message:
 * <tt>Reached maximum number of iterations</tt>
 *
 * @todo Handle the case of real matrices with pairs of complex conjugate eigenvalues.
 * @todo Handle the case of complex matrices.
 */
template <typename T>
Eigen::Vector<std::complex<double>, -1> QRMethod<T>::ComputeEigs() {
    // Initializing the necessary variables
    int rows, cols;
    rows = (this->_A).rows();
    cols = (this->_A).cols();
    int it; // Number of iterations
    Eigen::HouseholderQR<Eigen::Matrix<T, -1, -1>> QR(rows, cols); // To store the QR decomposition at each iteration
    Eigen::Matrix<T, -1, -1> A_k(rows, cols);
    Eigen::Matrix<T, -1, -1> A_next(rows, cols);

    // Setting the initial matrix
    A_next = this->_A;
    // Setting the iterations to zero and the residual such that the algorithm is not stopped at the first iteration
    it = 0;
    double res = (this->_tol + 1) * A_next.norm();

    // Loop
    while ((it < this->_maxit) && (res > this->_tol * A_next.diagonal().norm())){
        A_k = A_next;
        // Computing the QR factorization and A_next as R*Q
        QR = A_k.householderQr();
        A_next =  Eigen::Matrix<T, -1, -1>(QR.matrixQR().template triangularView<Eigen::Upper>()) * QR.householderQ();
        // Computing the residual and updating the iteration
        res = (A_k.diagonal() - A_next.diagonal()).norm();
        it++;
    }

    // If the maximum number of iteration is reached, a ConvergenceError is thrown.
    if (it == this->_maxit){
        throw(ConvergenceError("Reached maximum number of iterations"));
    }

    // Returning the eigenvalues
    Eigen::Vector<std::complex<double>, -1> eigs;
    eigs = A_next.diagonal();
    return eigs;
}

// Explicit instantiation for double
template class QRMethod<double>;
