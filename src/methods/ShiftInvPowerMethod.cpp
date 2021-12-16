#include "ShiftInvPowerMethod.h"

/**
 * @details The method has been overridden to add an initial step that computes the LU factorization of the shifted
 * matrix.
 */
template <typename T>
Eigen::Vector<std::complex<double>, -1> ShiftInvPowerMethod<T>::ComputeEigs() {
    _LU = (this->_A - this->_shift * Eigen::Matrix<T, -1, -1>::Identity((this->_A).rows(),
                                                                        (this->_A).cols())).fullPivLu();
    return AbstractPowerMethod<T>::ComputeEigs();
}

template <typename T>
Eigen::Vector<T, -1> ShiftInvPowerMethod<T>::Multiply(const Eigen::Vector<T, -1> &x) {
    // The multiplication is executed solving a system, given the already computed LU factorization of the shifted
    // matrix.
    return _LU.solve(x);
}

// Explicit instantiation for double and std::complex<double>
template class ShiftInvPowerMethod<double>;
template class ShiftInvPowerMethod<std::complex<double>>;

