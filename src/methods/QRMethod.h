#ifndef QRMETHOD_H
#define QRMETHOD_H

#include "AbstractEigs.h"

/** @class QRMethod
 * @brief Class for computing eigenvalues of general matrices using the QR Method.
 * @tparam T Can be only <tt>double</tt>.
 * @todo Extend also to <tt>std::complex<double></tt>
 * @details The QR method @cite GolubVanLoan computes all the eigenvalues of matrix.
 * The QR Method can be described in the following way:
 *  1. Set \f$A^{(0)} = A\f$
 *  2. At each iteration \f$k\f$:
 *      1. Compute the QR factorization of \f$A^{(k)} = QR\f$
 *      2. Set \f$A^{(k+1)} = RQ\f$
 *      3. If not converged, return to step 2.a
 *  3. If converged, return the diagonal of \f$A^{(k+1)}\f$
 *
 *  The stopping criterion that determines if the method converged is \f$||diag(A^{(k+1)}) - diag(A^{(k)})|| < \epsilon ||diag(A^{(k+1)})||\f$,
 *  where \f$\epsilon\f$ is a prescribed tolerance. In any case, the iterations are stopped when \f$k\f$ exceeds the
 *  maximum number of iterations and in this case the method is said to be non-convergent for the specific instance.
 *
 * If the matrix \f$A\f$ is real and has real eigenvalues, under some technical conditions the method is proved to
 * be convergent. In particular, the sequence of matrices \f$A^{(k)}\f$ converges an upper triangular matrix if the and
 * the diagonal elements of \f$A^{(k)}\f$ converge to the eigenvalues.
 * If the matrix is real but with complex conjugate eigenvalues, the sequence converges to an almost upper triangular
 * matrix, where the main subdiagonal has nonzero entries only when there is a complex conjugate pair of eigenvalues.
 * This second case is not handled by our implementation, that only works if the matrix is real with real eigenvalues.
 * @todo Handle the case of complex conjugate eigenvalues for real matrices.
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
    QRMethod<double> eigs_solver(A, tol, maxit);
    std::cout << "The eigenvalues of A computed using tolerance " << tol;
    std::cout << " and maximum number of iterations " << maxit << " are:\n" << eigs_solver.ComputeEigs();
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
    The eigenvalues of A computed using tolerance 1e-10 and maximum number of iterations 1000 are:
    (9,0)
    (7,0)
    (5,0)
    (3,0)
    (1,0)
 * @endcode
 */

template <typename T> class QRMethod : public AbstractEigs<T>{
public:
    /**
     * @copydoc AbstractEigs::AbstractEigs(const Eigen::Matrix<T, -1, -1> &A)
     */
    QRMethod(const Eigen::Matrix<T, -1, -1> &A) : AbstractEigs<T>(A) {};

    /**
     * @copydoc AbstractEigs::AbstractEigs(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const int &maxit)
     */
    QRMethod(const Eigen::Matrix<T, -1, -1> &A, const double &tol, const double &maxit) : AbstractEigs<T>(A, tol, maxit) {};

    /**
     * @copydoc  AbstractEigs::AbstractEigs(std::map<std::string, std::any> &map)
     */
    QRMethod(std::map<std::string, std::any> &map) : AbstractEigs<T>(map) {};

    // Destructor
    virtual ~QRMethod() override {};

    /**
     * @brief Returns the eigenvalues computed using the QR method.
     * @return Vector of complex numbers containing the eigenvalues computed using the QR method.
     */
    virtual Eigen::Vector<std::complex<double>, -1> ComputeEigs() override;
};

#endif //QRMETHOD_H_
