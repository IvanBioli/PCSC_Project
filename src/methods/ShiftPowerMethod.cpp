#include "ShiftPowerMethod.h"
/// CONSTRUCTORS
template <typename T>
ShiftPowerMethod<T>::ShiftPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit,
                                      const Eigen::Vector<T, -1> &x, const T &shift)
                                      : AbstractPowerMethod<T>(A, tol, maxit, x) {
    _shift = shift;
}

template <typename T>
ShiftPowerMethod<T>::ShiftPowerMethod(std::map<std::string, std::any> &map) : AbstractPowerMethod<T> (map) {
    // Shift
    if (map.count("shift") > 0) {
        T shift;
        try {
            shift = std::any_cast<T>(map["shift"]);
        }
        catch (std::bad_any_cast &e) {
            throw (InitializationError("Unable to cast the shift to the expected type"));
        }
        _shift = shift;
    }
    else { // map.count("shift") == 0
        std::cerr << "WARNING: Unspecified shift. Set by default shift = 0 (Power Method)." << std::endl;
    }
}

/// PRIVATE METHODS
template <typename T>
Eigen::Vector<T, -1> ShiftPowerMethod<T>::Multiply(const Eigen::Vector<T, -1> &x) {
    return this->_A * x - _shift * x;
}

// Needed for linking
template class ShiftPowerMethod<double>;
template class ShiftPowerMethod<std::complex<double>>;