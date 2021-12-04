#include "ShiftInvPowerMethod.h"

/// CONSTRUCTOR
template <typename T>
ShiftInvPowerMethod<T>::ShiftInvPowerMethod(std::map<std::string, std::any> &map) : InvPowerMethod<T>(map){
    throw(std::runtime_error("Not Implemented"));
}

/// COMPUTEIGS
template <typename T>
std::vector<std::complex<double>> ShiftInvPowerMethod<T>::ComputeEigs() {
    this->_LU = (this->_A - _shift * Eigen::Matrix<T, -1, -1>::Identity((this->_A).rows(), (this->_A).cols())).fullPivLu();
    return AbstractPowerMethod<T>::ComputeEigs();
}

// Needed for linking
template class ShiftInvPowerMethod<double>;
template class ShiftInvPowerMethod<std::complex<double>>;

