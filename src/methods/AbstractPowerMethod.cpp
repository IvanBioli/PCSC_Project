#include "AbstractPowerMethod.h"

/// CONSTRUCTORS
template <typename T>
AbstractPowerMethod<T>::AbstractPowerMethod(const Eigen::Matrix<T, -1, -1> &A) : AbstractEigs<T>(A) {
    // Setting by default the initial vector to the vector of all ones.
    _x0 = Eigen::Vector<T, -1>::Ones(A.cols());
}

template <typename T>
AbstractPowerMethod<T>::AbstractPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int maxit,
                                            const Eigen::Matrix<T, -1, 1> &x0) : AbstractEigs<T>(A, tol, maxit) {
    SetInitVec(x0);
}

template <typename T>
AbstractPowerMethod<T>::AbstractPowerMethod(std::map<std::string, std::any> &map) : AbstractEigs<T>(map) {
    // Vector
    if (map.count("x0") == 0) {
        std::cerr << "WARNING: Unspecified initial vector (x0). Set by default to vector of all ones" << std::endl;
        _x0 = Eigen::Vector<T, -1>::Ones(this->_A.cols());
    }
    else { // map.count("x0") == 0
        try {
            SetInitVec(std::any_cast<Eigen::Vector<T, -1>>(map["x0"]));
        }
        catch (std::bad_any_cast &e) {
            throw (InitializationError("Unable to cast the initial vector to the expected type"));
        }
    }
}

template <typename T>
void AbstractPowerMethod<T>::SetInitVec(const Eigen::Matrix<T, -1, 1> &x0) {
    if(x0.norm() < 1e-8){
        throw(InitializationError("Attempting to set initial vector with norm almost zero"));
    }
    if (x0.rows() != this -> _A.cols()){
        throw(InitializationError("Attempting to set initial vector with incorrect size"));
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
        it = it + 1;
    }
    if (it == this->_maxit){
        throw(ConvergenceError("Reached maximum number of iterations"));
    }
    // Returning the eigenvalue
    Eigen::Vector<std::complex<double>, 1> eigs;
    eigs[0] = _return(lambda);
    return eigs;
}

// Needed for linking
template class AbstractPowerMethod<double>;
template class AbstractPowerMethod<std::complex<double>>;
