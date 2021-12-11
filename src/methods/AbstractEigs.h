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

/** @class
 * TODO: General description of the AbstractEigs class
 *
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
