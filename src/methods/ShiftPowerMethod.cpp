#include "ShiftPowerMethod.h"
/// CONSTRUCTORS
template <typename T>
ShiftPowerMethod<T>::ShiftPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit,
                                      const Eigen::Vector<T, -1> &x, const double &shift)
                                      : AbstractPowerMethod<T>(A, tol, maxit, x) {
    _shift = shift;
}

template <typename T>
ShiftPowerMethod<T>::ShiftPowerMethod(const std::map<std::string, std::any> &map) : AbstractPowerMethod<T> (map) {
    throw (std::runtime_error("Not implemented"));
}

/// PRIVATE METHODS
template <typename T>
Eigen::Vector<T, -1> ShiftPowerMethod<T>::Multiply(const Eigen::Vector<T, -1> &x) {
    return this->_A * x - _shift * x;
}

// Needed for linking
template class ShiftPowerMethod<double>;
template class ShiftPowerMethod<std::complex<double>>;