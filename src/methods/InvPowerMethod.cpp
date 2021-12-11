#include "InvPowerMethod.h"

/**
 * @details The method has been overridden to add an initial step that computes the LU factorization of the matrix.
 */
template <typename T>
Eigen::Vector<std::complex<double>, -1> InvPowerMethod<T>::ComputeEigs() {
    _LU = this->_A.fullPivLu();
    return AbstractPowerMethod<T>::ComputeEigs();
}

template <typename T>
Eigen::Vector<T, -1> InvPowerMethod<T>::Multiply(const Eigen::Vector<T, -1> &x) {
    // The multiplication is executed solving a system, given the already computed LU factorization of the matrix whose
    // eigenvalues are to be computed.
    return _LU.solve(x);
}

// Explicit instantiation for double and std::complex<double>
template class InvPowerMethod<double>;
template class InvPowerMethod<std::complex<double>>;
