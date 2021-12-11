#ifndef ABSTRACTPOWERMETHOD_H_
#define ABSTRACTPOWERMETHOD_H_

#include "AbstractEigs.h"

/** @class
 * TODO: General description of the AbstractPowerMethod class
 * TODO: General description of the power method iteration scheme.
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
