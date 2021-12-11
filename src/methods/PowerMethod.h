#ifndef POWERMETHOD_H_
#define POWERMETHOD_H_

#include "AbstractPowerMethod.h"

/** @class
 * TODO: General description of the PowerMethod class
 * TODO: General description of the power method iteration.
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
