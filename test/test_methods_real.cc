#include <gtest/gtest.h>
#include <algorithm>
#include <memory>
#include <any>
#include <string>
#include "Eigen/Eigenvalues"
#include "Eigen/Dense"

#include "InvPowerMethod.h"
#include "PowerMethod.h"
#include "QRMethod.h"
#include "ShiftPowerMethod.h"
#include "ShiftInvPowerMethod.h"

#include "Exceptions.h"

// Copied from https://stackoverflow.com/questions/23270078/test-a-specific-exception-type-is-thrown-and-the-exception-has-the-right-propert
#define ASSERT_THROW_MSG(statement, expected_exception, expected_what)                    \
  try                                                                                     \
  {                                                                                       \
    statement;                                                                            \
    FAIL() << "Expected: " #statement " throws an exception of type " #expected_exception \
              ".\n"                                                                       \
              "  Actual: it throws nothing.";                                             \
  }                                                                                       \
  catch (const expected_exception& e)                                                     \
  {                                                                                       \
    ASSERT_EQ(expected_what, std::string{e.what()});                                      \
  }                                                                                       \
  catch (...)                                                                             \
  {                                                                                       \
    FAIL() << "Expected: " #statement " throws an exception of type " #expected_exception \
              ".\n"                                                                       \
              "  Actual: it throws a different type.";                                    \
  }

class MethodsTest_real : public ::testing::Test {
protected:
    int n = 4;  // Size of the matrix
    Eigen::Matrix<double, -1, -1> A; // Matrix
    Eigen::Vector<double, -1> x0; // Initial vector
    double tol; // Tolerance
    double maxit; // Maximum number of iterations
    double shift; // Shift for the shifted methods
    Eigen::Vector<std::complex<double>, 4> exact_eigs; // Vector to store the eigenvalues computed using the Eigen library
    std::unique_ptr<AbstractEigs<double>> p_eigsSolver_double;
    std::map<std::string, std::any> map;

    void SetUp() override {
        // TODO: BETTER UNDERSTANDING OF THE SETUP
        // Initializing the inputs of the methods
        A.resize(n,n);
        A << 5, -2, -1, 0, -2, 5, -1, -1, -1, -1, 4, -1, 0, -1, -1, 5;
        map["matrix"] = A;
        x0.resize(n);
        x0 << 1, 1, 1, 1;
        map["x0"] = x0;
        tol = 1e-10;
        map["tol"] = tol;
        maxit = 1000;
        map["maxit"] = maxit;
        // Computing the eigenvalues using Eigen library and sorting them in descending order of absolute value
        exact_eigs = A.eigenvalues();
        auto abs_complex = [](std::complex<double> i, std::complex<double> j) { return abs(i) > abs(j);};
        std::sort(exact_eigs.data(),exact_eigs.data()+exact_eigs.size(), abs_complex);
    }

    void TearDown() override {}
};


// TESTING THE INSTANTIATION AND THE INITIALIZATION OF THE CLASSES DERIVED FROM AbstractEigs
TEST_F(MethodsTest_real, PowerMethodsInitialization){
    /* Testing constructors and methods for initializing the PowerMethod class.
     * Tests for constructors and methods directly inherited from AbstractEigs and AbstractPower classes with no
     * overriding are valid also for all other classes that directly inherit them.
     */

    std::unique_ptr<PowerMethod<double>> p_powerMethod;

    // Testing the constructors
    p_powerMethod = std::make_unique<PowerMethod<double>>(A);
    ASSERT_TRUE(A.isApprox(p_powerMethod->GetMatrix(), 1e-16));

    p_powerMethod.reset(new PowerMethod<double>(A, tol, maxit, x0));
    ASSERT_TRUE(A.isApprox(p_powerMethod->GetMatrix()));
    ASSERT_TRUE(p_powerMethod->GetMaxit() == maxit);
    ASSERT_TRUE(p_powerMethod->GetTol() == tol);
    ASSERT_TRUE(x0.isApprox(p_powerMethod->GetInitVec(), 1e-16));

    p_powerMethod.reset(new PowerMethod<double>(map));
    ASSERT_TRUE(A.isApprox(p_powerMethod->GetMatrix()));
    ASSERT_TRUE(p_powerMethod->GetMaxit() == maxit);
    ASSERT_TRUE(p_powerMethod->GetTol() == tol);
    ASSERT_TRUE(x0.isApprox(p_powerMethod->GetInitVec(), 1e-16));

    // Testing the expected exceptions and the relative error message
    // Attempting to set a non square matrix
    Eigen::Matrix<double, -1, -1> B(n,n-1);
    B = Eigen::Matrix<double, -1, -1>::Zero(n, n-1);
    ASSERT_THROW_MSG(p_powerMethod.reset(new PowerMethod<double>(B)), InitializationError, "Attempting to set a non square matrix");

    // Attempting to set tolerance <= 0
    ASSERT_THROW_MSG(p_powerMethod->SetTol(-1), InitializationError, "Attempting to set tolerance <= 0");
    ASSERT_THROW_MSG(p_powerMethod->SetTol(0), InitializationError, "Attempting to set tolerance <= 0");

    // Attempting to set maximum number of iteration <= 0
    ASSERT_THROW_MSG(p_powerMethod->SetMaxit(-1), InitializationError, "Attempting to set maximum number of iteration <= 0");
    ASSERT_THROW_MSG(p_powerMethod->SetMaxit(0), InitializationError, "Attempting to set maximum number of iteration <= 0");

    // Attempting to set initial vector with incorrect size
    p_powerMethod.reset(new PowerMethod<double>(A));
    Eigen::Vector<double, -1> x0_new(n-1);
    x0_new = Eigen::Vector<double, -1>::Ones(n-1);
    ASSERT_THROW_MSG(p_powerMethod->SetInitVec(x0_new), InitializationError, "Attempting to set initial vector with incorrect size");

    // Attempting to set initial vector with norm almost zero
    x0_new.resize(n);
    x0_new = Eigen::Vector<double, -1>::Zero(n-1);
    ASSERT_THROW_MSG(p_powerMethod->SetInitVec(x0_new), InitializationError, "Attempting to set initial vector with norm almost zero");

    // Missing argument in the input map: matrix
    std::map<std::string, std::any> map_new(map);
    map_new.erase("matrix");
    ASSERT_THROW_MSG(p_powerMethod.reset(new PowerMethod<double>(map_new)), InitializationError, "Missing argument: matrix");
}

TEST_F(MethodsTest_real, ShiftMethodsInitialization){
    std::unique_ptr<ShiftPowerMethod<double>> p_shiftPowerMethod;

    // Testing the constructors that are not directly inherited from the AbstractEigs or the AbstractPowerMethod classes
    shift = 5;
    p_shiftPowerMethod = std::make_unique<ShiftPowerMethod<double>>(A, tol, maxit, x0, shift);
    ASSERT_TRUE(p_shiftPowerMethod->GetShift() == shift);

    map["shift"] = shift;
    p_shiftPowerMethod.reset(new ShiftPowerMethod<double>(map));
    ASSERT_TRUE(p_shiftPowerMethod->GetShift() == shift);
}

// TESTING THE METHODS FOR COMPUTING EIGENVALUES OF THE CLASSES DERIVED FROM AbstractEigs
TEST_F(MethodsTest_real, PowerMethod){
    p_eigsSolver_double = std::make_unique<PowerMethod<double>>(A, tol, maxit, x0);
    EXPECT_NEAR(exact_eigs[0].real(), p_eigsSolver_double->ComputeEigs()[0].real() ,1e-8);
    EXPECT_NEAR(exact_eigs[0].imag(), p_eigsSolver_double->ComputeEigs()[0].imag() ,1e-8);
}

TEST_F(MethodsTest_real, InvPowerMethod){
    p_eigsSolver_double = std::make_unique<InvPowerMethod<double>>(A, tol, maxit, x0);
    EXPECT_NEAR(exact_eigs[3].real(), p_eigsSolver_double->ComputeEigs()[0].real() ,1e-8);
    EXPECT_NEAR(exact_eigs[3].imag(), p_eigsSolver_double->ComputeEigs()[0].imag() ,1e-8);
}

TEST_F(MethodsTest_real, ShiftPowerMethod){
    shift = 7;
    p_eigsSolver_double = std::make_unique<ShiftPowerMethod<double>>(A, tol, maxit, x0, shift);
    EXPECT_NEAR(exact_eigs[3].real(), p_eigsSolver_double->ComputeEigs()[0].real() ,1e-8);
    EXPECT_NEAR(exact_eigs[3].imag(), p_eigsSolver_double->ComputeEigs()[0].imag() ,1e-8);
}

TEST_F(MethodsTest_real, ShiftInvPowerMethod) {
    shift = 4;
    p_eigsSolver_double = std::make_unique<ShiftInvPowerMethod<double>>(A, tol, maxit, x0, shift);
    EXPECT_NEAR(exact_eigs[2].real(), p_eigsSolver_double->ComputeEigs()[0].real(), 1e-8);
    EXPECT_NEAR(exact_eigs[2].imag(), p_eigsSolver_double->ComputeEigs()[0].imag(), 1e-8);
}

TEST_F(MethodsTest_real, QRMethod){
    p_eigsSolver_double = std::make_unique<QRMethod<double>>(A, tol, maxit);
    for (int i = 0; i < 4; i++) {
        EXPECT_NEAR(exact_eigs[i].real(), p_eigsSolver_double->ComputeEigs()[i].real() ,1e-8);
        EXPECT_NEAR(exact_eigs[i].imag(), p_eigsSolver_double->ComputeEigs()[i].imag() ,1e-8);
    }
}