#include "ShiftInvPowerMethod.h"

/// COMPUTEIGS
template <typename T>
Eigen::Vector<std::complex<double>, -1> ShiftInvPowerMethod<T>::ComputeEigs() {
    _LU = (this->_A - this->_shift * Eigen::Matrix<T, -1, -1>::Identity((this->_A).rows(), (this->_A).cols())).fullPivLu();
    return AbstractPowerMethod<T>::ComputeEigs();
}

/// MULTIPLY METHOD
template <typename T>
Eigen::Vector<T, -1> ShiftInvPowerMethod<T>::Multiply(const Eigen::Vector<T, -1> &x) {
    return _LU.solve(x);
}
// Needed for linking
template class ShiftInvPowerMethod<double>;
template class ShiftInvPowerMethod<std::complex<double>>;

