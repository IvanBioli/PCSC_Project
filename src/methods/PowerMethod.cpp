#include "PowerMethod.h"

template <typename T>
Eigen::Vector<T, -1> PowerMethod<T>::Multiply(const Eigen::Vector<T, -1> &x) {
    return this->_A * x;
}

// Needed for linking
template class PowerMethod<double>;
template class PowerMethod<std::complex<double>>;