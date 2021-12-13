#ifndef ABSTRACTPOWERMETHOD_H_
#define ABSTRACTPOWERMETHOD_H_

#include "AbstractEigs.h"

/** @class AbstractPowerMethod
 * @brief Abstract class to compute eigenvalues of general matrices using the power method scheme.
 * @tparam T Can be <tt>double</tt> or <tt>std::complex<double></tt>.
 * @details The Power Method @cite GolubVanLoan computes the largest magnitude eigenvalue of a matrix \f$A\f$.
 * The Power Method can be described in the following way:
 *  1. Starting from an initial nonzero vector \f$x^{(0)}\f$, divide it by its norm: \f$x^{(0)} = x^{(0)} / ||x^{(0)}||\f$
 *  2. At each iteration \f$k\f$:
 *      1. \f$x^{(k+1)} = Ax^{(k)} / ||Ax^{(k)}||\f$
 *      2. \f$\lambda^{(k+1)} = x^{(k+1)}\cdot Ax^{(k+1)}\f$
 *      3. If not converged, return to step 2.1
 *
 *  The stopping criterion that determines if the method converged is \f$|\lambda^{(k+1)} - \lambda^{(k)}| < \epsilon |\lambda^{(k+1)}|\f$,
 *  where \f$\epsilon\f$ is a prescribed tolerance. In any case, the iterations are stopped when \f$k\f$ exceeds the
 *  maximum number of iterations and in this case the method is said to be non-convergent for the specific instance.
 *  @see PowerMethod
 *
 *  The Inverse Power Method @cite GolubVanLoan computes the smallest magnitude eigenvalue of a non singular matrix
 *  \f$A\f$. It basically consists in the Power Method applied to the matrix \f$A^{-1}\f$.
 *  @see InvPowerMethod
 *
 *  The Power Method with shift @cite GolubVanLoan computes eigenvalue of \f$A\f$ farthest from a particular value
 *  \f$\sigma\f$. It basically consists in the Power Method applied to the matrix \f$A - \sigma I\f$.
 *  @see ShiftPowerMethod
 *
 *  The Inverse Power Method with shift @cite GolubVanLoan computes eigenvalue of \f$A\f$ closest a particular value
 *  \f$\sigma\f$. It basically consists in the Power Method applied to the matrix \f$(A - \sigma I)^{-1}\f$, if it is
 *  non singular.
 *  @see ShiftInvPowerMethod
 *
 *
 *  All the previous methods exploit the general scheme of the Power Method, using a different matrix. Therefore, what
 *  differs is just the multiplication step, i.e. the computation of \f$Mx^{(k)}\f$ where \f$M = A \f$ for the Power
 *  Method, \f$M = A^{-1} \f$ for the Inverse Power Method, \f$M = (A - \sigma I)\f$ for the Power Method with shift and
 *  \f$M = (A - \sigma I)^{-1}\f$ for the Inverse Power Method with shift. Therefore, this class exploits the pure
 *  virtual protected method AbstractPowerMethod::Multiply(const Eigen::Vector<T,-1> &x) to implement the general Power Method scheme. The
 *  specific method is distinguished by the definition of the Multiply method in the corresponding derived class.
 */

template <typename T> class AbstractPowerMethod : public AbstractEigs<T>{
protected:

    /** @brief Initial vector.
     * @details Initial vector for the iterations of the method.
     * It has to be non zero vector.
     * */
    Eigen::Vector<T,-1> _x0;

    /**
     * Protected method to execute the multiplication step according to the method.
     * @param x vector to be multiplied.
     * @return Result of the multiplication step.
     */
    virtual Eigen::Vector<T,-1> Multiply(const Eigen::Vector<T,-1> &x) = 0;

    // Function to return the eigenvalue of the matrix _A
    virtual T _return(T &lambda) = 0;

public:
    /**
     * @copydoc AbstractEigs::AbstractEigs(const Eigen::Matrix<T, -1, -1> &A)
     */
    AbstractPowerMethod(const Eigen::Matrix<T, -1, -1> &A);

    /**
     * @brief Constructor; sets the given matrix, tolerance, maximum number of iterations and initial vector.
     * @param A Square matrix whose eigenvalues are to be computed.
     * @param tol Tolerance to be used in the stopping criterion of the method.
     * @param maxit Maximum number of iterations for which the method is to be executed.
     * @param x0 Initial vector for the iterations of the method.
     * @details This constructor is useful in cases in which the user already knows which tolerance, maximum number of
     * iterations and initial vector to use in the method.
     */
    AbstractPowerMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int maxit,
                        const Eigen::Matrix<T,-1,1> &x0);

    /**
     * @brief Constructor; sets the parameters of the method from a map.
     * @param map Map containing the parameters of the method. The matrix whose eigenvalues are to be computed has to be
     * associated with the key <tt>matrix</tt>, the tolerance with <tt>tol</tt>, the maximum number of iterations
     * with <tt>maxit</tt> and the initial vector with <tt>x0</tt>.
     */
    AbstractPowerMethod(std::map<std::string, std::any> &map);

    // Destructor
    virtual ~AbstractPowerMethod() override {};

    /**
     * @brief Sets the initial vector.
     * @param x0 Initial vector for the iterations of the method.
     */
    void SetInitVec(const Eigen::Matrix<T,-1,1> &x0);

    /**
     * @brief Returns the initial vector.
     */
    Eigen::Vector<T,-1> GetInitVec() {return _x0;};

    /**
     * @brief Returns the eigenvalues computed according to the method.
     * @return Vector of complex numbers containing the eigenvalues computed according to one of the schemes of the
     * power method iteration.
     */
    virtual Eigen::Vector<std::complex<double>, -1> ComputeEigs() override;
};

#endif //ABSTRACTPOWERMETHOD_H_
