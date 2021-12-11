#include "AbstractPowerMethod.h"


// Constructors
/**
 * Sets the given matrix and sets by default the initial vector to a vector of all ones.
 */
template <typename T>
AbstractPowerMethod<T>::AbstractPowerMethod(const Eigen::Matrix<T, -1, -1> &A) : AbstractEigs<T>(A) {
    // Setting by default the initial vector to the vector of all ones.
    _x0 = Eigen::Vector<T, -1>::Ones(A.cols());
}

/**
 * @details This constructor is useful in cases in which the user already knows which tolerance, maximum number of
 * iterations and initial vector to use in the method.
 */
template <typename T>
AbstractPowerMethod<T>::AbstractPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int maxit,
                                            const Eigen::Matrix<T, -1, 1> &x0) : AbstractEigs<T>(A, tol, maxit) {
    SetInitVec(x0);
}

/**
 * @details At least the matrix has to be provided. If the initial vector is not provided, it is set by default to a
 * vector of all ones and a warning is given to the user. If the tolerance or the maximum number of iterations are not
 * provided, they are set to the default value and a warning is given to the user.
 */
template <typename T>
AbstractPowerMethod<T>::AbstractPowerMethod(std::map<std::string, std::any> &map) : AbstractEigs<T>(map) {
    // // Getting and setting the initial vector
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

//Setting methods
/**
 * @details If the given initial vector has a norm lower than \f$ 10^{-8}\f$, it throws an exception of type
 * InitializationError with message: <tt>Attempting to set initial vector with norm almost zero</tt>.
 *
 * If the size of the initial vector does not match the size of the matrix whose eigenvalues are to be computed, it
 * throws an exception of type InitializationError with message: <tt>Attempting to set initial vector with incorrect size</tt>.
 */
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

/**
 * @details Computes the eigenvalues following the general scheme of a power method iteration. The method changes
 * according to how the multiplication step is executed.
 *
 * If the maximum number of iterations is reached it throws an error or type ConvergenceError with message:
 * <tt>Reached maximum number of iterations</tt>
 */
template <typename T>
Eigen::Vector<std::complex<double>, -1> AbstractPowerMethod<T>::ComputeEigs() {
    // Initializing the necessary variables
    Eigen::Vector<T, -1> x; // Vector before the multiplication step
    Eigen::Vector<T, -1> x_mul; // Vector after the multiplication step
    int it; // Number of iterations
    T lambda; // Current approximation of the eigenvalue
    T lambda_prev; // Approximation of the eigenvalue at the previous iteration
    double res; // Residual

    // First iteration outside the loop, necessary for having an initial approximation of lambda.
    x = _x0 / _x0.norm();
    x_mul = Multiply(x);
    lambda = x.adjoint() * x_mul;

    // Setting iterations to 1 and residual such that the algorithm is not stopped
    it = 1;
    res = (this->_tol + 1) * std::abs(lambda);

    // Loop
    while ((res > this->_tol * std::abs(lambda)) && (it < this->_maxit)) {
        // Normalization and multiplication step
        x = x_mul / x_mul.norm();
        x_mul = Multiply(x);
        // Computing the approximation of the eigenvalue
        lambda_prev = lambda;
        lambda = x.adjoint() * x_mul;
        // Computing the residual and updating the iteration
        res = std::abs(lambda - lambda_prev);
        it++;
    }

    // If the maximum number of iteration is reached, a ConvergenceError is thrown.
    if (it == this->_maxit){
        throw(ConvergenceError("Reached maximum number of iterations"));
    }

    // Returning the eigenvalue
    Eigen::Vector<std::complex<double>, 1> eigs;
    eigs[0] = _return(lambda);
    return eigs;
}

// Explicit instantiation for double and std::complex<double>
template class AbstractPowerMethod<double>;
template class AbstractPowerMethod<std::complex<double>>;
