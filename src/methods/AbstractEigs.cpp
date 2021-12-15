#include "AbstractEigs.h"

// CONSTRUCTORS
/**
 * @details This constructor is useful in cases in which the user wants to set just the matrix whose eigenvalues are to
 * be computed and then experiment the method with different values of the other parameters of the method.
 */
template <typename T>
AbstractEigs<T>::AbstractEigs(const Eigen::Matrix<T, -1, -1> &A) {
    SetMatrix(A);
}

/**
 * @details This constructor is useful in cases in which the user already knows which tolerance and maximum number of
 * iterations to use in the method.
 */
template <typename T>
AbstractEigs<T>::AbstractEigs(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit) {
    SetMatrix(A);
    SetTol(tol);
    SetMaxit(maxit);
}

/**
 * @details This constructor is useful in cases in which the user reads the input from a file and wants to pass it to
 * the eigenvalues problem solver in a format such that is the solver itself who picks the arguments it needs.
 *
 * At least the matrix has to be provided. If the tolerance or the maximum number of iterations are not provided they
 * are set to the default value and a warning is given to the user.
 */
template <typename T>
AbstractEigs<T>::AbstractEigs(std::map<std::string, std::any> &map) {
    // Getting and setting the matrix
    if (map.count("matrix") == 0) {
        throw(InitializationError("Missing argument: matrix"));
    }
    try {
        SetMatrix(std::any_cast<Eigen::Matrix<T, -1, -1>>(map["matrix"]));
    }
    catch (std::bad_any_cast &e){
        throw(InitializationError("Unable to cast the matrix to the expected type"));
    }

    // Getting and setting the tolerance
    if (map.count("tol") > 0) {
        double tol;
        try {
            tol = std::any_cast<double>(map["tol"]);
        }
        catch (std::bad_any_cast &e) {
            throw (InitializationError("Unable to cast the tolerance to double"));
        }
        SetTol(tol);
    }
    else { // map.count("tol") == 0
        std::cerr << "WARNING: Unspecified tolerance (tol). Set by default tol = 1e-8" << std::endl;
    }

    // Getting and setting the maximum number of iterations
    if (map.count("maxit") > 0) {
        double maxit;
        try {
            maxit = std::any_cast<double>(map["maxit"]);
        }
        catch (std::bad_any_cast &e) {
            throw (InitializationError("Unable to cast the maxit to double"));
        }
        if (maxit != int(maxit)) {
            std::cerr << "WARNING: maximum number of iterations is not an integer. Truncated to its floor"
                      << std::endl;
        }
        SetMaxit(int(maxit));
    }
    else {// map.count("tol") == 0
        std::cerr << "WARNING: Unspecified maximum number of iterations (maxit). Set by default maxit = 10000" << std::endl;
    }
}

// SETTING METHODS
/**
 * @details If the given tolerance is lower than or equal to zero, it throws an exception of type InitializationError
 * with message: <tt>Attempting to set tolerance <= 0</tt>.
 */
template <typename T>
void AbstractEigs<T>::SetTol(const double &tol) {
    if (tol <= 0){
        throw(InitializationError("Attempting to set tolerance <= 0"));
    }
    _tol = tol;
}

/**
 * @details If the given maximum number of iterations is lower than or equal to zero, it throws an exception of type
 * InitializationError with message: <tt>Attempting to set maximum number of iteration <= 0</tt>.
 */
template <typename T>
void AbstractEigs<T>::SetMaxit(const int &maxit) {
    if (maxit <= 0){
        throw(InitializationError("Attempting to set maximum number of iteration <= 0"));
    }
    _maxit = maxit;
}

/**
 * @details Protected method to set the matrix whose eigenvalues are to be computed.
 * If the given matrix is non square, it throws an exception of type InitializationError with message: <tt>Attempting to set a
 * non square matrix</tt>.
 */
template <typename T>
void AbstractEigs<T>::SetMatrix(const Eigen::Matrix<T, -1, -1> &A) {
    if (A.rows() != A.cols()){
        throw(InitializationError("Attempting to set a non square matrix"));
    }
    _A = A;
}

// Explicit instantiation for double and std::complex<double>
template class AbstractEigs<double>;
template class AbstractEigs<std::complex<double>>;