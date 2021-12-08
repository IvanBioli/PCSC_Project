#include "AbstractEigs.h"

/// CONSTRUCTORS
// Constructor that initializes the matrix only
template <typename T>
AbstractEigs<T>::AbstractEigs(const Eigen::Matrix<T, -1, -1> &A) {
    SetMatrix(A);
}

// Constructor that initializes the matrix, the tolerance and the maximum number of iterations
template <typename T>
AbstractEigs<T>::AbstractEigs(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit) {
    SetMatrix(A);
    SetTol(tol);
    SetMaxit(maxit);
}

/* Constructor that initializes the matrix, the tolerance and the maximum number of iterations from a map that
 * associates each key to the corresponding member.
 */
template <typename T>
AbstractEigs<T>::AbstractEigs(std::map<std::string, std::any> &map) {
    // Matrix
    if (map.count("matrix") == 0) {
        throw(InitializationError("Missing argument: matrix"));
    }
    try {
        SetMatrix(std::any_cast<Eigen::Matrix<T, -1, -1>>(map["matrix"]));
    }
    catch (std::bad_any_cast &e){
        throw(InitializationError("Unable to cast the matrix to the expected type"));
    }

    // Tolerance
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

    // Checking the maxit
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

/// SETTING METHODS
// Method that sets the matrix
template <typename T>
void AbstractEigs<T>::SetMatrix(const Eigen::Matrix<T, -1, -1> &A) {
    if (A.rows() != A.cols()){
        throw(InitializationError("Attempting to set a non square matrix"));
    }
    _A = A;
}

// Method that sets the tolerance
template <typename T>
void AbstractEigs<T>::SetTol(const double &tol) {
    if (tol <= 0){
        throw(InitializationError("Attempting to set tolerance <= 0"));
    }
    _tol = tol;
}

// Method that sets the tolerance
template <typename T>
void AbstractEigs<T>::SetMaxit(const int &maxit) {
    if (maxit <= 0){
        throw(InitializationError("Attempting to set maximum number of iteration <= 0"));
    }
    _maxit = maxit;
}

// Needed for linking
template class AbstractEigs<double>;
template class AbstractEigs<std::complex<double>>;