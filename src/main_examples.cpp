#include <iostream>
#include <complex>
#include <string>
#include <exception>
#include <memory>
#include <Eigen/Dense>

#include "AbstractEigs.h"
#include "AbstractPowerMethod.h"
#include "InvPowerMethod.h"
#include "PowerMethod.h"
#include "QRMethod.h"
#include "ShiftPowerMethod.h"
#include "ShiftInvPowerMethod.h"

#include "Reader.h"
#include "FileReader.h"

int main(int argc, char **argv) {
    /*
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
    */
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
    /*
    double tol = 1e-10;
    int maxit = 1000;
    double shift = 6;
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
    ShiftPowerMethod<double> eigs_solver(A, tol, maxit, x0, shift);
    std::cout << "The eigenvalue of A farthest from " << shift << " computed using tolerance " << tol;
    std::cout << " and maximum number of iterations " << maxit << " is:\n" << eigs_solver.ComputeEigs();

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
    */
    /*
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
    */
}