#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <stdexcept>

/**
 * @brief Exception class for errors in opening a file.
 * @details Used in the FileReader class.
 */
class FileNotOpen : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

/**
 * @brief Exception class for errors in the initialization of a method for computing eigenvalues.
 * @details Used in the derived classes of the class AbstractEigs .
 */
class InitializationError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

/**
 * @brief Exception class for errors in the convergence of a method for computing eigenvalues.
 * @details Used in the derived classes of the class AbstractEigs .
 */
class ConvergenceError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

#endif //EXCEPTIONS_H_
