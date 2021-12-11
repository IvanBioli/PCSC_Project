#ifndef INVPOWERMETHOD_H_
#define INVPOWERMETHOD_H_

#include "AbstractPowerMethod.h"

/** @class
 * TODO: General description of the InvPowerMethod class
 * TODO: General description of the inverse power method iteration.
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
