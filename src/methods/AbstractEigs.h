#ifndef ABSTRACTEIGS_H_
#define ABSTRACTEIGS_H_

#include <Eigen/Dense>
#include <iostream>
#include <complex>
#include <vector>
#include <map>
#include <string>
#include <any>
#include "Exceptions.h"

/** @class AbstractEigs
 * @brief Abstract class for computing eigenvalues of general matrices.
 * @tparam T Can be <tt>double</tt> or <tt>std::complex<double></tt>.
 * @details The eigenvalues and eigenvectors of a square matrix \f$A\f$ of size \f$n\f$ are scalars \f$\lambda\f$ and vectors \f$v\neq0\f$
 * such that \f$Av = \lambda v\f$. The previous equation can be written as \f$(A - \lambda I)v\f$, therefore
 * \f$\lambda\f$ is an eigenvalues of \f$A\f$ if and only if the matrix \f$A-\lambda I\f$ is singular, hence if and only
 * if \f$\lambda\f$ is a root of the characteristic polynomial \f$p(\lambda) = det(A-\lambda I)\f$. This is a polynomial
 * of degree \f$n\f$ in \f$\lambda\f$ so there are exactly \f$n\f$ complex roots. Even if the matrix real its eigenvalues
 * can be complex, but in this case the characteristic polynomial has real coefficients and therefore the complex roots
 * occur in conjugate pairs. For the previous reason, even if the matrix is real, the return type of the method
 * ComputeEigs() is <tt>Eigen::Vector<std::complex<double>, -1></tt>
 *
 * In literature many iterative methods for computing approximation of eigenvalues have been developed. The derived classes
 * of this AbstractEigs abstract class compute (some of) the eigenvalues of the matrix \f$A\f$ using different iterative
 * methods.
 *
 * One of the most used methods to compute all the eigenvalues at one time is the QR method @cite GolubVanLoan .
 * Call the function QRMethod::ComputeEigs() to have returned all the eigenvectors of a real matrix, computed using the
 * QR Method. @see QRMethod
 *
 * Sometimes not all eigenvalues are necessary for the problem at hand. Some specific methods, less heavy than th QR
 * method from a computational point of view. In particular:
 *  - to compute the largest magnitude eigenvalue, the Power Method @cite GolubVanLoan can be used. Call the function
 *  PowerMethod::ComputeEigs() to have returned the largest magnitude eigenvalue of a real or complex matrix, computed
 *  using the Power Method.
 *  @see PowerMethod
 *  - to compute the smallest magnitude eigenvalue, the Inverse Power Method @cite GolubVanLoan can be used. Call the function
 *  InvPowerMethod::ComputeEigs() to have returned the smallest magnitude eigenvalue of a real or complex matrix, computed
 *  using the Inverse Power Method.
 *  @see InvPowerMethod
 *  - to compute the eigenvalue farthest from a particular value \f$\sigma\f$, the Power Method with shift @cite GolubVanLoan
 *  \f$\sigma\f$ can be used. Call the function ShiftPowerMethod::ComputeEigs() to have returned the eigenvalue
 *  farthest to a previously set shift \f$\sigma\f$, computed using the Power Method with shift.
 *  @see ShiftPowerMethod
 *  - to compute the eigenvalue closest to a particular value \f$\sigma\f$, the Inverse Power Method with shift @cite GolubVanLoan
 *  \f$\sigma\f$ can be used. Call the function ShiftInvPowerMethod::ComputeEigs() to have returned the eigenvalue
 *  closest to a previously set shift \f$\sigma\f$, computed using the Inverse Power Method with shift.
 *  @see ShiftInvPowerMethod
 */
template <typename T> class AbstractEigs {
protected:

    /** @brief Matrix
     * @details Square matrix whose eigenvalues are to be computed.
     * */
    Eigen::Matrix<T,-1,-1> _A;

    /**
     * @brief Tolerance
     * @details Tolerance to be used in the stopping criterion of the method.
     * It has to be a real number greater than zero.
     * Default value: \f$10^{-8}\f$.
     */
    double _tol = 1e-8;

    /**
     * @brief Maximum number of iterations
     * @details Maximum number of iterations for which the method is to be executed.
     * It has to be an integer grater than zero.
     * Default value: \f$10000\f$.
     */
    int _maxit = 10000;

    /**
     * @brief Protected method to set the matrix.
     * @param A Square matrix whose eigenvalues are to be computed.
     */
    void SetMatrix(const Eigen::Matrix<T, -1, -1> &A);

public:

    /**
     * @brief Constructor; sets the given matrix.
     * @param A Square matrix whose eigenvalues are to be computed.
     */
    AbstractEigs(const Eigen::Matrix<T, -1, -1> &A);

    /**
     * @brief Constructor; sets the given matrix, tolerance and maximum number of iterations.
     * @param A Square matrix whose eigenvalues are to be computed.
     * @param tol Tolerance to be used in the stopping criterion of the method.
     * @param maxit Maximum number of iterations for which the method is to be executed.
     */
    AbstractEigs(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit);

    /**
     * @brief Constructor; sets the parameters of the method from a map.
     * @param map Map containing the parameters of the method. The matrix whose eigenvalues are to be computed has to be
     * associated with the key <tt>matrix</tt>, the tolerance with <tt>tol</tt> and the maximum number of iterations
     * with <tt>maxit</tt>.
     */
    AbstractEigs(std::map<std::string, std::any> &map);

    // Destructor
    virtual ~AbstractEigs(){};

    /**
     * @brief Sets the to be used in the stopping criterion of the method.
     * @param tol Tolerance to be used in the stopping criterion of the method.
     */
    void SetTol(const double &tol);

    /**
     * @brief Sets the maximum number of iterations allowed.
     * @param maxit Maximum number of iterations for which the method is to be executed.
     */
    void SetMaxit(const int &maxit);

    /**
     * @brief Returns the matrix whose eigenvalues are to be computed.
     */
    Eigen::Matrix<T,-1,-1> GetMatrix() {return _A;};

    /**
     * @brief Returns the tolerance used in the stopping criterion of the method.
     */
    double GetTol() {return _tol;};

    /**
     * @brief Returns the maximum number of iterations for which the method is executed.
     */
    int GetMaxit() {return _maxit;};

    /**
     * @brief Returns the eigenvalues computed according to the method.
     * @return Vector of complex numbers containing the eigenvalues computed according to the method.
     */
    virtual Eigen::Vector<std::complex<double>, -1> ComputeEigs() = 0;
};


#endif //ABSTRACTEIGS_H_
