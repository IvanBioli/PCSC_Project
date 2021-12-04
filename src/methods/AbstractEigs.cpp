#include "AbstractEigs.h"

/// CONSTRUCTORS
// Constructor that initializes the matrix only
template <typename T>
AbstractEigs<T>::AbstractEigs(const Eigen::Matrix<T, -1, -1> &A) {
    _A = A;
}

// Constructor that initializes the matrix, the tolerance and the maximum number of iterations
template <typename T>
AbstractEigs<T>::AbstractEigs(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit) {
    _A = A;
    if (tol <= 0){
        throw(std::runtime_error("Tolerance<=0"));
    }
    _tol = tol;
    // SHOULD WE DO
    // SetTolt(tol)

    if (maxit <= 0){
        throw(std::runtime_error("Maxit<=0"));
    }
    _maxit = maxit;
}

/* Constructor that initializes the matrix, the tolerance and the maximum number of iterations from a map that
 * associates each key to the corresponding member.
 */
template <typename T>
AbstractEigs<T>::AbstractEigs(const std::map<std::string, std::any> &map) {
    throw(std::runtime_error("Not Implemented"));
}

/// SETTING METHODS
// Method that sets the matrix
template <typename T>
void AbstractEigs<T>::SetMatrix(const Eigen::Matrix<T, -1, -1> &A) {
    _A = A;
}

// Method that sets the tolerance
template <typename T>
void AbstractEigs<T>::SetTol(const double &tol) {
    if (tol <= 0){
        throw(std::runtime_error("Tolerance<=0"));
    }
    _tol = tol;
}

// Method that sets the tolerance
template <typename T>
void AbstractEigs<T>::SetMaxit(const int &maxit) {
    if (maxit <= 0){
        throw(std::runtime_error("Maxit<=0"));
    }
    _maxit = maxit;
}

// Needed for linking
template class AbstractEigs<double>;
template class AbstractEigs<std::complex<double>>;