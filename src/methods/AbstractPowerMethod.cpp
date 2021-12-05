#include "AbstractPowerMethod.h"

/// CONSTRUCTORS
template <typename T>
AbstractPowerMethod<T>::AbstractPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int maxit,
                                            const Eigen::Matrix<T, -1, 1> &x0) : AbstractEigs<T>(A, tol, maxit) {
    if(x0.norm() < 1e-8){
        throw(std::runtime_error("Zero initial vector"));
    }
    _x0 = x0;
}

template <typename T>
AbstractPowerMethod<T>::AbstractPowerMethod(const std::map<std::string, std::any> &map) : AbstractEigs<T>(map) {
    throw(std::runtime_error("Not implemented"));
}

template <typename T>
void AbstractPowerMethod<T>::SetInitVec(const Eigen::Matrix<T, -1, 1> &x0) {
    if(x0.norm() < 1e-8){
        throw(std::runtime_error("Zero initial vector"));
    }
    _x0 = x0;
}

/// Power method
template <typename T>
Eigen::Vector<std::complex<double>, -1> AbstractPowerMethod<T>::ComputeEigs() {
    Eigen::Vector<T, -1> x, x_mul;
    int it;
    T lambda, lambda_prev;
    double res;
    // First iteration outside the loop, necessary for iteration.
    x = _x0 / _x0.norm();
    x_mul = Multiply(x);
    lambda = x.adjoint() * x_mul;
    // Setting iterations to 1 and residual such that the algorithm is not stopped
    it = 1;
    res = (this->_tol + 1) * std::abs(lambda);
    while ((res > this->_tol * std::abs(lambda)) && (it < this->_maxit)) {
        x = x_mul / x_mul.norm();
        x_mul = Multiply(x);
        // Computing the approximation of the eigenvalue
        lambda_prev = lambda;
        lambda = x.adjoint() * x_mul;
        // Residual for the stopping criterion
        res = std::abs(lambda - lambda_prev);
    }
    if (it == this->_maxit){
        throw(std::runtime_error("Reached maximum number of iterations"));
    }
    // Returning the eigenvalue
    Eigen::Vector<std::complex<double>, 1> eigs;
    eigs[0] = _return(lambda);
    return eigs;
}

// Needed for linking
template class AbstractPowerMethod<double>;
template class AbstractPowerMethod<std::complex<double>>;
