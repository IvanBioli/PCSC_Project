#ifndef SHIFTINVPOWERMETHOD_H_
#define SHIFTINVPOWERMETHOD_H_

#include "ShiftPowerMethod.h"

template <typename T> class ShiftInvPowerMethod : public ShiftPowerMethod<T> {
public:
    /**
     * @copydoc  ShiftPowerMethod::ShiftPowerMethod(const Eigen::Matrix<T, -1, -1> &A)
     */
    ShiftInvPowerMethod(const Eigen::Matrix<T, -1, -1> &A) : ShiftPowerMethod<T>(A) {};

    /**
     * @copydoc  ShiftPowerMethod::ShiftPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit, const Eigen::Vector<T, -1> &x0, const T &shift)
     */
    ShiftInvPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit,
                        const Eigen::Vector<T,-1> &x0, const T &shift) :
                        ShiftPowerMethod<T>(A, tol, maxit, x0, shift) {};

    /**
     * @copydoc ShiftPowerMethod::ShiftPowerMethod(std::map<std::string, std::any> &map)
     */
    ShiftInvPowerMethod(std::map<std::string, std::any> &map) : ShiftPowerMethod<T>(map) {};

    // Destructor
    virtual ~ShiftInvPowerMethod() override {};

    /**
     * @brief Returns the eigenvalues computed using the inverse power method with shift.
     * @return Vector of complex numbers containing the eigenvalue of \f$A\f$ that is the closest to the shift.
     */
    Eigen::Vector<std::complex<double>, -1> ComputeEigs() override;

private:
    /**
     * @brief Member that stores the LU factorization of the shifted matrix.
     */
    Eigen::FullPivLU<Eigen::Matrix<T, -1, -1>> _LU;

    // Function to return the eigenvalue of the matrix _A. For the inverse power method with shift, it coincides with
    // 1 / lambda + _shift where lambda is the value computed applying the power method to the inverse of the shifted
    // matrix.
    T _return(T &lambda) override {return (double(1) / lambda + this->_shift);};

    /**
     * @brief Executes the multiplication step of the inverse power method with shift.
     * @param x vector to be multiplied.
     * @return Result of the multiplication step, i.e. \f$ (A-sI)^{-1}x\f$.
     */
    Eigen::Vector<T,-1> Multiply(const Eigen::Vector<T,-1> &x) override;


};

#endif //SHIFTINVPOWERMETHOD_H_
