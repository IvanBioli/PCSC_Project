#ifndef SHIFTPOWERMETHOD_H_
#define SHIFTPOWERMETHOD_H_

#include "AbstractPowerMethod.h"

/** @class ShiftPowerMethod
 * @brief Class for computing the the eigenvalue of a matrix \f$A\f$ farthes from a particular value \f$\sigma\f$ using the
 * Power Method with shift.
 * @tparam T Can be <tt>double</tt> or <tt>std::complex<double></tt>.
 * @details The Power Method with shift @cite GolubVanLoan computes the the eigenvalue of a matrix \f$A\f$ farthest from
 * a particular value \f$\sigma\f$.
 * The Power Method with shift can be described in the following way:
 *  1. Starting from an initial nonzero vector \f$x^{(0)}\f$, divide it by its norm: \f$x^{(0)} = x^{(0)} / ||x^{(0)}||\f$
 *  2. At each iteration \f$k\f$:
 *      1. \f$x^{(k+1)} = (A - \sigma I)x^{(k)} / ||(A - \sigma I)x^{(k)}||\f$
 *      2. \f$\mu^{(k+1)} = x^{(k+1)}\cdot (A - \sigma I)x^{(k+1)}\f$
 *      3. If not converged, return to step 3.a
 *  3. If converged, return \f$\lambda = \mu^{(k+1)} + \sigma\f$
 *
 *  The stopping criterion that determines if the method converged is \f$|\mu^{(k+1)} - \mu^{(k)}| < \epsilon |\mu^{(k+1)}|\f$,
 *  where \f$\epsilon\f$ is a prescribed tolerance. In any case, the iterations are stopped when \f$k\f$ exceeds the
 *  maximum number of iterations and in this case the method is said to be non-convergent for the specific instance.
 *
 *  Usage:
 *  @code{.cpp}
    double tol = 1e-10;
    int maxit = 1000;
    double shift = 6;
    Eigen::Matrix<double, -1, -1> A(5,5);
    A <<    1, 28 , 48, -52, -8,
            2, -17, -42, 24, 2,
            0, 12, 25, -12 , 0,
            2, 0, -4 , 11, 2,
            -4, -4, 12, 16, 5;
    Eigen::Vector<double, -1> x0(5);
    x0 << 1, 1, 1, 1, 1;
    std::cout << "Here is a matrix A:\n" << A << std::endl;
    std::cout << "and an initial vector x0 (transposed): " << x0.transpose() << std::endl;
    ShiftPowerMethod<double> eigs_solver(A, tol, maxit, x0, shift);
    std::cout << "The eigenvalue of A farthest from " << shift << " computed using tolerance " << tol;
    std::cout << " and maximum number of iterations " << maxit << " is:\n" << eigs_solver.ComputeEigs();
 *  @endcode
 *
 *  Output
 *  @code{.unparsed}
    Here is a matrix A:
      1  28  48 -52  -8
      2 -17 -42  24   2
      0  12  25 -12   0
      2   0  -4  11   2
     -4  -4  12  16   5
    and an initial vector x0 (transposed): 1 1 1 1 1
    The eigenvalue of A farthest from 6 computed using tolerance 1e-10 and maximum number of iterations 1000 is:
    (1,0)
 *  @endcode
 */
template <typename T> class ShiftPowerMethod : public AbstractPowerMethod<T>{
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
};
#endif //SHIFTPOWERMETHOD_H_
