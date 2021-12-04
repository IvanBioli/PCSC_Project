#include "InvPowerMethod.h"

template <typename T>
std::vector<std::complex<double>> InvPowerMethod<T>::ComputeEigs() {
    _LU = this->_A.fullPivLu();
    return AbstractPowerMethod<T>::ComputeEigs();
}

/// MULTIPLY METHOD
template <typename T>
Eigen::Vector<T, -1> InvPowerMethod<T>::Multiply(const Eigen::Vector<T, -1> &x) {
    return _LU.solve(x);
}

// Needed for linking
template class InvPowerMethod<double>;
template class InvPowerMethod<std::complex<double>>;
