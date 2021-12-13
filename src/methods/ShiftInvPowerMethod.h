#ifndef SHIFTINVPOWERMETHOD_H_
#define SHIFTINVPOWERMETHOD_H_

#include "ShiftPowerMethod.h"

/** @class ShiftInvPowerMethod
 * @brief Class for computing the the eigenvalue of a matrix \f$A\f$ closest to a particular value \f$\sigma\f$ using the Inverse
 * Power Method with shift.
 * @tparam T Can be <tt>double</tt> or <tt>std::complex<double></tt>.
 * @details The Inverse Power Method with shift @cite GolubVanLoan computes the the eigenvalue of a matrix \f$A\f$
 * closest to a particular value \f$\sigma\f$.
 * The Inverse Power Method with shift can be described in the following way:
 *  1. Starting from an initial nonzero vector \f$x^{(0)}\f$, divide it by its norm: \f$x^{(0)} = x^{(0)} / ||x^{(0)}||\f$
 *  2. Compute the LU factorization of \f$A - \sigma I\f$
 *  3. At each iteration \f$k\f$:
 *      1. Solve \f$(A - \sigma I)x^{(k+1)} = x^{(k)}\f$
 *      2. \f$x^{(k+1)} = x^{(k+1)} / ||x^{(k+1)}||\f$
 *      3. \f$\mu^{(k+1)} = x^{(k+1)}\cdot (A - \sigma I)^{(-1)}x^{(k+1)}\f$ (without solving the system again)
 *      4. If not converged, return to step 3.a
 *  4. If converged, return \f$\lambda = (1 / \mu^{(k+1)}) + \sigma\f$
 *
 *  The stopping criterion that determines if the method converged is \f$|\mu^{(k+1)} - \mu^{(k)}| < \epsilon |\mu^{(k+1)}|\f$,
 *  where \f$\epsilon\f$ is a prescribed tolerance. In any case, the iterations are stopped when \f$k\f$ exceeds the
 *  maximum number of iterations and in this case the method is said to be non-convergent for the specific instance.
 *
 *  Usage:
 *  @code{.cpp}
    double tol = 1e-10;
    int maxit = 1000;
    double shift = 6.5;
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
    ShiftInvPowerMethod<double> eigs_solver(A, tol, maxit, x0, shift);
    std::cout << "The eigenvalue of A closest to " << shift << " computed using tolerance " << tol;
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
    The eigenvalue of A closest to 6.5 computed using tolerance 1e-10 and maximum number of iterations 1000 is:
    (7,0)
 *  @endcode
 */
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
