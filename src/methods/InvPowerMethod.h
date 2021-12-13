#ifndef INVPOWERMETHOD_H_
#define INVPOWERMETHOD_H_

#include "AbstractPowerMethod.h"

/** @class InvPowerMethod
 * @brief Class for computing the smallest magnitude eigenvalue of general matrices using the Inverse Power Method.
 * @tparam T Can be <tt>double</tt> or <tt>std::complex<double></tt>.
 * @details The Inverse Power Method @cite GolubVanLoan computes the smallest magnitude eigenvalue of a non singular
 * matrix \f$A\f$.
 * The Inverse Power Method can be described in the following way:
 *  1. Starting from an initial nonzero vector \f$x^{(0)}\f$, divide it by its norm: \f$x^{(0)} = x^{(0)} / ||x^{(0)}||\f$
 *  2. Compute the LU factorization of \f$A\f$
 *  3. At each iteration \f$k\f$:
 *      1. Solve \f$Ax^{(k+1)} = x^{(k)}\f$
 *      2. \f$x^{(k+1)} = x^{(k+1)} / ||x^{(k+1)}||\f$
 *      3. \f$\mu^{(k+1)} = x^{(k+1)}\cdot A^{(-1)}x^{(k+1)}\f$ (without solving the system again)
 *      4. If not converged, return to step 3.a
 *  4. If converged, return \f$\lambda = 1 / \mu^{(k+1)}\f$
 *
 *  The stopping criterion that determines if the method converged is \f$|\mu^{(k+1)} - \mu^{(k)}| < \epsilon |\mu^{(k+1)}|\f$,
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
    InvPowerMethod<double> eigs_solver(A, tol, maxit, x0);
    std::cout << "The smallest magnitude eigenvalue computed using tolerance " << tol;
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
    The smallest magnitude eigenvalue computed using tolerance 1e-10 and maximum number of iterations 1000 is:
    (1,0)
 *  @endcode
 */

template <typename T> class InvPowerMethod : public AbstractPowerMethod<T>{
public:

    /**
     * @copydoc AbstractPowerMethod::AbstractPowerMethod(const Eigen::Matrix<T, -1, -1> &A)
     */
    InvPowerMethod(const Eigen::Matrix<T, -1, -1> &A) : AbstractPowerMethod<T>(A) {};

    /**
     * @copydoc AbstractPowerMethod::AbstractPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int maxit, const Eigen::Matrix<T,-1,1> &x0)
     */
    InvPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit,
                   const Eigen::Vector<T,-1> &x0) : AbstractPowerMethod<T>(A, tol, maxit, x0) {};

    /**
     * @copydoc  AbstractPowerMethod::AbstractPowerMethod(std::map<std::string, std::any> &map)
     */
    InvPowerMethod(std::map<std::string, std::any> &map) : AbstractPowerMethod<T>(map) {};

    // Destructor
    virtual ~InvPowerMethod() override {};

    /**
     * @brief Returns the eigenvalues computed using the inverse power method.
     * @return Vector of complex numbers containing the eigenvalue of \f$A\f$ with the smallest absolute value.
     */
    virtual Eigen::Vector<std::complex<double>, -1> ComputeEigs() override;

private:
    /**
     * @brief Member that stores the LU factorization of the matrix whose eigenvalues are to be computed.
     */
    Eigen::FullPivLU<Eigen::Matrix<T, -1, -1>> _LU;

    // Function to return the eigenvalue of the matrix _A. For the inverse power method, it coincides with 1/lambda
    // where lambda is the value computed applying the power method to the inverse of _A.
    T _return(T &lambda) override {return (double(1) / lambda);};

    /**
     * @brief Executes the multiplication step of the inverse power method.
     * @param x vector to be multiplied.
     * @return Result of the multiplication step, i.e. \f$ A^{-1}\,x \f$.
     */
    Eigen::Vector<T,-1> Multiply(const Eigen::Vector<T,-1> &x) override;
};

#endif //INVPOWERMETHOD_H_
