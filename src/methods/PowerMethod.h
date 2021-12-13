#ifndef POWERMETHOD_H_
#define POWERMETHOD_H_

#include "AbstractPowerMethod.h"

/** @class PowerMethod
 * @brief Class for computing the largest magnitude eigenvalue of general matrices using the Power Method.
 * @tparam T Can be <tt>double</tt> or <tt>std::complex<double></tt>.
 * @details The Power Method @cite GolubVanLoan computes the largest magnitude eigenvalue of a matrix \f$A\f$.
 * The Power Method can be described in the following way:
 *  1. Starting from an initial nonzero vector \f$x^{(0)}\f$, divide it by its norm: \f$x^{(0)} = x^{(0)} / ||x^{(0)}||\f$
 *  2. At each iteration \f$k\f$:
 *      1. \f$x^{(k+1)} = Ax^{(k)} / ||Ax^{(k)}||\f$
 *      2. \f$\lambda^{(k+1)} = x^{(k+1)}\cdot Ax^{(k+1)}\f$
 *      3. If not converged, return to step 2.a
 *  3. If converged, return \f$\lambda^{(k+1)}\f$
 *
 *  The stopping criterion that determines if the method converged is \f$|\lambda^{(k+1)} - \lambda^{(k)}| < \epsilon |\lambda^{(k+1)}|\f$,
 *  where \f$\epsilon\f$ is a prescribed tolerance. In any case, the iterations are stopped when \f$k\f$ exceeds the
 *  maximum number of iterations and in this case the method is said to be non-convergent for the specific instance.
 *
 *  Usage:
 *  @code{.cpp}
    double tol = 1e-10;
    int maxit = 1000;
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
    PowerMethod<double> eigs_solver(A, tol, maxit, x0);
    std::cout << "The largest magnitude eigenvalue computed using tolerance " << tol;
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
  The largest magnitude eigenvalue computed using tolerance 1e-10 and maximum number of iterations 1000 is:
  (9,0)
 *  @endcode
 */

template <typename T> class PowerMethod : public AbstractPowerMethod<T>{
public:

    /**
     * @copydoc AbstractPowerMethod::AbstractPowerMethod(const Eigen::Matrix<T, -1, -1> &A)
     */
    PowerMethod(const Eigen::Matrix<T, -1, -1> &A) : AbstractPowerMethod<T>(A) {};

    /**
     * @copydoc AbstractPowerMethod::AbstractPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int maxit, const Eigen::Matrix<T,-1,1> &x0)
     */
    PowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit, const Eigen::Vector<T,-1> &x0)
    : AbstractPowerMethod<T>(A, tol, maxit, x0) {};

    /**
     * @copydoc AbstractPowerMethod::AbstractPowerMethod(std::map<std::string, std::any> &map)
     */
    PowerMethod(std::map<std::string, std::any> &map) : AbstractPowerMethod<T>(map) {};

    // Destructor
    virtual ~PowerMethod() override {};

private:

    // Function to return the eigenvalue of the matrix _A. For the power method, it coincides with the lambda computed
    // by the power iteration.
    T _return(T &lambda) override {return lambda;};

    /**
     * @brief Executes the multiplication step of the power method.
     * @param x vector to be multiplied.
     * @return Result of the multiplication step, i.e. \f$ A\,x \f$.
     */
    Eigen::Vector<T,-1> Multiply(const Eigen::Vector<T,-1> &x) override {return this->_A * x;};
};

#endif //POWERMETHOD_H_
