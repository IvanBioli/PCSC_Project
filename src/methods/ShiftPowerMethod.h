#ifndef SHIFTPOWERMETHOD_H_
#define SHIFTPOWERMETHOD_H_

#include "AbstractPowerMethod.h"

template <typename T> class ShiftPowerMethod : public AbstractPowerMethod<T>{
protected:

    /**
     * @brief Shift applied to the matrix.
     * @details Default value: \f$0\f$.
     */
    T _shift = 0;

private:

    // Function to return the eigenvalue of the matrix _A. For the power method with shift, it coincides with
    // lambda + _shift where lambda is the value computed applying the power method to the shifted matrix.
    T _return(T &lambda) override {return lambda + _shift;};

    /**
     * @brief Executes the multiplication step of the power method with shift.
     * @param x vector to be multiplied.
     * @return Result of the multiplication step, i.e. \f$ (A-sI)x = Ax - sx\f$.
     */
    virtual Eigen::Vector<T,-1> Multiply(const Eigen::Vector<T,-1> &x) override {return this->_A * x - _shift * x;};

public:
    /**
     * @copydoc AbstractEigs<T>::AbstractEigs(const Eigen::Matrix<T, -1, -1> &A)
     */
    ShiftPowerMethod(const Eigen::Matrix<T, -1, -1> &A) : AbstractPowerMethod<T>(A) {};

    /**
     * @brief Constructor; sets the given matrix, tolerance, maximum number of iterations initial vector ans shift.
     * @param A Square matrix whose eigenvalues are to be computed.
     * @param tol Tolerance to be used in the stopping criterion of the method.
     * @param maxit Maximum number of iterations for which the method is to be executed.
     * @param x0 Initial vector for the iterations of the method.
     * @param shift Shift applied to the matrix.
     * @details This constructor is useful in cases in which the user already knows which tolerance, maximum number of
     * iterations, initial vector ans shift to use in the method.
     */
    ShiftPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit,
                     const Eigen::Vector<T, -1> &x0, const T &shift) : AbstractPowerMethod<T>(A, tol, maxit, x0)
                             {_shift = shift;};

    /**
     * @brief Constructor; sets the parameters of the method from a map.
     * @param map Map containing the parameters of the method. The matrix whose eigenvalues are to be computed has to be
     * associated with the key <tt>matrix</tt>, the tolerance with <tt>tol</tt>, the maximum number of iterations
     * with <tt>maxit</tt>, the initial vector with <tt>x0</tt> and the shift with <tt>shift</tt>.
     */
    ShiftPowerMethod(std::map<std::string, std::any> &map);

    // Destructor
    virtual ~ShiftPowerMethod() override {};

    /**
     * @brief Sets the shift.
     * @param shift Shift applied to the matrix.
     */
    void SetShift(const T &shift) {_shift = shift;};

    /**
     * @brief Returns the shift.
     */
    T GetShift() {return _shift;};

};
#endif //SHIFTPOWERMETHOD_H_
