#include <gtest/gtest.h>
#include <algorithm>
#include <memory>
#include "Eigen/Eigenvalues"
#include "Eigen/Dense"

#include "InvPowerMethod.h"
#include "PowerMethod.h"
#include "QRMethod.h"
#include "ShiftPowerMethod.h"
#include "ShiftInvPowerMethod.h"

using c = std::complex<double>;
class MethodsTest_complex : public ::testing::Test {
protected:
    void SetUp() override {
        // Initializing the inputs of the methods
        A <<    c(5, 1), c(-2, 1), c(-1, 3) , c(0, 4),
                c(-2, 2), c(5, 3), c(-1, 4), c(-1, 1),
                c(-1, 1), c(-1, 3), c(4, 2), c(-1, 4),
                c(0, 3), c(-1, 4), c(-1, 2), c(5, 1);
        std::cout << A << std::endl;
        // TODO: BETTER UNDERSTANDING OF THE SETUP
        x0 << 1, 1, 1, 1;
        tol = 1e-10;
        itmax = 1000;
        // Computing the eigenvalues using Eigen library and sorting them in descending order of absolute value
        exact_eigs = A.eigenvalues();
        auto abs_complex = [](std::complex<double> i, std::complex<double> j) { return abs(i) > abs(j);};
        std::sort(exact_eigs.data(),exact_eigs.data()+exact_eigs.size(), abs_complex);
    }

    void TearDown() override {}

    int n = 4;  // Size of the matrix
    Eigen::Matrix<std::complex<double>, 4, 4> A; // Matrix
    Eigen::Vector<std::complex<double>, 4> x0; // Initial vector
    double tol; // Tolerance
    double itmax; // Maximum number of iterations
    std::complex<double> shift; // Shift for the shifted methods
    Eigen::Vector<std::complex<double>, 4> exact_eigs; // Vector to store the eigenvalues computed using the Eigen library
    std::unique_ptr<AbstractEigs<std::complex<double>>> p_eigsSolver_complex;
};

TEST_F(MethodsTest_complex, PowerMethod){
    p_eigsSolver_complex = std::make_unique<PowerMethod<std::complex<double>>>(A, tol, itmax, x0);
    EXPECT_NEAR(exact_eigs[0].real(), p_eigsSolver_complex->ComputeEigs()[0].real() ,1e-8);
    EXPECT_NEAR(exact_eigs[0].imag(), p_eigsSolver_complex->ComputeEigs()[0].imag() ,1e-8);
}

TEST_F(MethodsTest_complex, InvPowerMethod){
    p_eigsSolver_complex = std::make_unique<InvPowerMethod<std::complex<double>>>(A, tol, itmax, x0);
    EXPECT_NEAR(exact_eigs[3].real(), p_eigsSolver_complex->ComputeEigs()[0].real() ,1e-8);
    EXPECT_NEAR(exact_eigs[3].imag(), p_eigsSolver_complex->ComputeEigs()[0].imag() ,1e-8);
}

TEST_F(MethodsTest_complex, ShiftPowerMethod){
    shift = c(7);
    p_eigsSolver_complex = std::make_unique<ShiftPowerMethod<std::complex<double>>>(A, tol, itmax, x0, shift);
    EXPECT_NEAR(exact_eigs[0].real(), p_eigsSolver_complex->ComputeEigs()[0].real() ,1e-8);
    EXPECT_NEAR(exact_eigs[0].imag(), p_eigsSolver_complex->ComputeEigs()[0].imag() ,1e-8);
}

TEST_F(MethodsTest_complex, ShiftInvPowerMethod) {
    shift = c(3, -2);
    p_eigsSolver_complex = std::make_unique<ShiftInvPowerMethod<std::complex<double>>>(A, tol, itmax, x0, shift);
    EXPECT_NEAR(exact_eigs[3].real(), p_eigsSolver_complex->ComputeEigs()[0].real(), 1e-8);
    EXPECT_NEAR(exact_eigs[3].imag(), p_eigsSolver_complex->ComputeEigs()[0].imag(), 1e-8);
}

// TODO: UNDERSTAND IF THE QR METHOD WORKS FOR COMPLEX MATRICES
/*
TEST_F(MethodsTest_complex, QRMethod){
    p_eigsSolver_complex = std::make_unique<QRMethod<std::complex<double>>>(A, 1e-4, itmax);
    for (int i = 0; i < 4; i++) {
        EXPECT_NEAR(exact_eigs[i].real(), p_eigsSolver_complex->ComputeEigs()[i].real() ,1e-2);
        EXPECT_NEAR(exact_eigs[i].imag(), p_eigsSolver_complex->ComputeEigs()[i].imag() ,1e-2);
    }
}
 */