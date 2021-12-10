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

// Adapted from https://stackoverflow.com/questions/23270078/test-a-specific-exception-type-is-thrown-and-the-exception-has-the-right-propert
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


// TODO: ORGANIZE THE TESTS INHERITANCE AS THE ONE OF THE ABSTRACTEIGS CLASSES
// TODO: ADD TEST FOR CONVERGENCE ERROR
template <typename T>
class MethodsTest : public ::testing::Test {
protected:

    int n = 5;  // Size of the matrix
    Eigen::Matrix<T, -1, -1> A; // Matrix
    Eigen::Vector<T, -1> x0; // Initial vector
    double tol; // Tolerance
    double maxit; // Maximum number of iterations
    T shift; // Shift for the shifted methods
    Eigen::Vector<std::complex<double>, -1> exact_eigs; // Vector to store the exact eigenvalues
    Eigen::Vector<std::complex<double>, -1> computed_eigs; // Vector to store the computed eigenvalues
    std::unique_ptr<AbstractEigs<T>> p_eigsSolver;
    std::map<std::string, std::any> map;

    void Initialization();

    void SetUp() override {
        // Initializing the inputs of the methods
        Initialization();
        x0 = Eigen::Vector<T, -1>::Ones(n);
        tol = 1e-10;
        maxit = 1000;

        // Construction of the map
        map["matrix"] = A;
        map["x0"] = x0;
        map["tol"] = tol;
        map["maxit"] = maxit;

        // Sorting the eigenvalues in descending order of absolute value
        auto abs_complex = [](std::complex<double> i, std::complex<double> j) { return abs(i) > abs(j);};
        std::sort(exact_eigs.data(),exact_eigs.data()+exact_eigs.size(), abs_complex);
    }

    void TearDown() override {}
};

template<>
void MethodsTest<double>::Initialization() {
    // Setting the matrix
    A.resize(n,n);
    A <<    1, 28 , 48, -52, -8,
            2, -17, -42, 24, 2,
            0, 12, 25, -12 , 0,
            2, 0, -4 , 11, 2,
            -4, -4, 12, 16, 5;

    // Setting the exact eigenvalues
    exact_eigs.resize(n);
    exact_eigs << 9, 7, 5, 3, 1;

    // Setting the shift
    shift = 4.5;
    map["shift"] = shift;
}

template<>
void MethodsTest<std::complex<double>>::Initialization() {
    // Setting the matrix
    using c = std::complex<double>;
    A.resize(n,n);
    A <<    c(-6, -1), c(4, -4), c(-1, -11), c(8, -8), c(0,0),
            c(-10, -4), c(5, -6), c(-8, -18), c(4, -10), c(0,0),
            c(6, 2), c(-4, 4), c(1, 12), c(-8, 8), c(0,0),
            c(1, -2), c(6, -3), c(15, -10), c(15, -7), c(0,0),
            c(8, 3), c(-6, 3), c(-6, 11), c(-6, 9), c(9,2);
    /*
    -6.0000 - 1.0000i   4.0000 - 4.0000i  -1.0000 -11.0000i   8.0000 - 8.0000i   0.0000 + 0.0000i
    -10.0000 - 4.0000i   5.0000 - 6.0000i  -8.0000 -18.0000i   4.0000 -10.0000i   0.0000 + 0.0000i
    6.0000 + 2.0000i  -4.0000 + 4.0000i   1.0000 +12.0000i  -8.0000 + 8.0000i   0.0000 + 0.0000i
    1.0000 - 2.0000i   6.0000 - 3.0000i  15.0000 -10.0000i  15.0000 - 7.0000i   0.0000 + 0.0000i
    8.0000 + 3.0000i  -6.0000 + 3.0000i  -6.0000 +11.0000i  -6.0000 + 9.0000i   9.0000 + 2.0000i
    */

    // Setting the exact eigenvalues
    exact_eigs.resize(n);
    exact_eigs << c(0, 1), c(3, -1), c(5,0), c(7,-2), c(9,2);
    /*
     0.0000 + 1.0000i   3.0000 - 1.0000i   5.0000 + 0.0000i   7.0000 - 2.0000i   9.0000 + 2.0000i
     */

    // Setting the shift
    shift = c(4,1);
    map["shift"] = shift;
}

// Class for testing methods defined only for double matrices (QRMethod)
typedef MethodsTest<double> MethodsTest_double;

// Typed test suite
typedef testing::Types<double, std::complex<double>> eigsTypes ;
TYPED_TEST_SUITE(MethodsTest, eigsTypes);

// TESTING THE INSTANTIATION AND THE INITIALIZATION OF THE CLASSES DERIVED FROM AbstractEigs
TYPED_TEST(MethodsTest, PowerMethodsInitialization){
    /* Testing constructors and methods for initializing the PowerMethod class.
     * Tests for constructors and methods directly inherited from AbstractEigs and AbstractPower classes with no
     * overriding are valid also for all other classes that directly inherit them.
     */
    
    std::unique_ptr<PowerMethod<TypeParam>> p_powerMethod;
    // Testing the constructors
    p_powerMethod = std::make_unique<PowerMethod<TypeParam>>(this->A);
    ASSERT_TRUE(this->A.isApprox(p_powerMethod->GetMatrix(), 0));

    p_powerMethod.reset(new PowerMethod<TypeParam>(this->A, this->tol, this->maxit, this->x0));
    ASSERT_TRUE(this->A.isApprox(p_powerMethod->GetMatrix()));
    ASSERT_TRUE(p_powerMethod->GetMaxit() == this->maxit);
    ASSERT_TRUE(p_powerMethod->GetTol() == this->tol);
    ASSERT_TRUE(this->x0.isApprox(p_powerMethod->GetInitVec(), 0));

    p_powerMethod.reset(new PowerMethod<TypeParam>(this->map));
    ASSERT_TRUE(this->A.isApprox(p_powerMethod->GetMatrix()));
    ASSERT_TRUE(p_powerMethod->GetMaxit() == this->maxit);
    ASSERT_TRUE(p_powerMethod->GetTol() == this->tol);
    ASSERT_TRUE(this->x0.isApprox(p_powerMethod->GetInitVec(), 0));

    // Testing the expected exceptions and the relative error message
    // Attempting to set a non square matrix
    Eigen::Matrix<TypeParam, -1, -1> B(this->n,this->n-1);
    B = Eigen::Matrix<TypeParam, -1, -1>::Zero(this->n, this->n-1);
    ASSERT_THROW_MSG(p_powerMethod.reset(new PowerMethod<TypeParam>(B)), InitializationError, "Attempting to set a non square matrix");

    // Attempting to set tolerance <= 0
    ASSERT_THROW_MSG(p_powerMethod->SetTol(-1), InitializationError, "Attempting to set tolerance <= 0");
    ASSERT_THROW_MSG(p_powerMethod->SetTol(0), InitializationError, "Attempting to set tolerance <= 0");

    // Attempting to set maximum number of iteration <= 0
    ASSERT_THROW_MSG(p_powerMethod->SetMaxit(-1), InitializationError, "Attempting to set maximum number of iteration <= 0");
    ASSERT_THROW_MSG(p_powerMethod->SetMaxit(0), InitializationError, "Attempting to set maximum number of iteration <= 0");

    // Attempting to set initial vector with incorrect size
    p_powerMethod.reset(new PowerMethod<TypeParam>(this->A));
    Eigen::Vector<TypeParam, -1> x0_new(this->n-1);
    x0_new = Eigen::Vector<TypeParam, -1>::Ones(this->n-1);
    ASSERT_THROW_MSG(p_powerMethod->SetInitVec(x0_new), InitializationError, "Attempting to set initial vector with incorrect size");

    // Attempting to set initial vector with norm almost zero
    x0_new.resize(this->n);
    x0_new = Eigen::Vector<TypeParam, -1>::Zero(this->n-1);
    ASSERT_THROW_MSG(p_powerMethod->SetInitVec(x0_new), InitializationError, "Attempting to set initial vector with norm almost zero");

    // Missing argument in the input map: matrix
    std::map<std::string, std::any> map_new(this->map);
    map_new.erase("matrix");
    ASSERT_THROW_MSG(p_powerMethod.reset(new PowerMethod<TypeParam>(map_new)), InitializationError, "Missing argument: matrix");
}


TYPED_TEST(MethodsTest, ShiftMethodsInitialization){
    std::unique_ptr<ShiftPowerMethod<TypeParam>> p_shiftPowerMethod;

    // Testing the constructors that are not directly inherited from the AbstractEigs or the AbstractPowerMethod classes
    p_shiftPowerMethod = std::make_unique<ShiftPowerMethod<TypeParam>>(this->A, this->tol, this->maxit, this->x0, this->shift);
    ASSERT_TRUE(p_shiftPowerMethod->GetShift() == this->shift);

    p_shiftPowerMethod.reset(new ShiftPowerMethod<TypeParam>(this->map));
    ASSERT_TRUE(p_shiftPowerMethod->GetShift() == this->shift);
}

// TESTING THE METHODS FOR COMPUTING EIGENVALUES OF THE CLASSES DERIVED FROM AbstractEigs
TYPED_TEST(MethodsTest, PowerMethod){
    this->p_eigsSolver = std::make_unique<PowerMethod<TypeParam>>(this->A, this->tol, this->maxit, this->x0);
    this->computed_eigs = this->p_eigsSolver->ComputeEigs();
    EXPECT_NEAR(this->exact_eigs[0].real(), this->computed_eigs[0].real() ,1e-8);
    EXPECT_NEAR(this->exact_eigs[0].imag(), this->computed_eigs[0].imag() ,1e-8);
    this->p_eigsSolver.reset(new PowerMethod<TypeParam>(this->A, this->tol, 3, this->x0));
    ASSERT_THROW_MSG(this->p_eigsSolver->ComputeEigs(), ConvergenceError, "Reached maximum number of iterations");
}

TYPED_TEST(MethodsTest, InvPowerMethod){
    this->p_eigsSolver = std::make_unique<InvPowerMethod<TypeParam>>(this->A, this->tol, this->maxit, this->x0);
    this->computed_eigs = this->p_eigsSolver->ComputeEigs();
    EXPECT_NEAR(this->exact_eigs[this->n-1].real(), this->computed_eigs[0].real() ,1e-8);
    EXPECT_NEAR(this->exact_eigs[this->n-1].imag(), this->computed_eigs[0].imag() ,1e-8);
}

TYPED_TEST(MethodsTest, ShiftPowerMethod){
    this->p_eigsSolver = std::make_unique<ShiftPowerMethod<TypeParam>>(this->A, this->tol, this->maxit, this->x0, this->shift);
    this->computed_eigs = this->p_eigsSolver->ComputeEigs();
    EXPECT_NEAR(this->exact_eigs[0].real(), this->computed_eigs[0].real() ,1e-8);
    EXPECT_NEAR(this->exact_eigs[0].imag(), this->computed_eigs[0].imag() ,1e-8);
}

TYPED_TEST(MethodsTest, ShiftInvPowerMethod) {
    this->p_eigsSolver = std::make_unique<ShiftInvPowerMethod<TypeParam>>(this->A, this->tol, this->maxit, this->x0, this->shift);
    this->computed_eigs = this->p_eigsSolver->ComputeEigs();
    EXPECT_NEAR(this->exact_eigs[2].real(), this->computed_eigs[0].real(), 1e-8);
    EXPECT_NEAR(this->exact_eigs[2].imag(), this->computed_eigs[0].imag(), 1e-8);
}


TEST_F(MethodsTest_double, QRMethod){
    this->p_eigsSolver = std::make_unique<QRMethod<double>>(this->A, this->tol, this->maxit);
    this->computed_eigs = this->p_eigsSolver->ComputeEigs();
    for (int i = 0; i < 4; i++) {
        EXPECT_NEAR(this->exact_eigs[i].real(), this->computed_eigs[i].real(), 1e-8);
        EXPECT_NEAR(this->exact_eigs[i].imag(), this->computed_eigs[i].imag(), 1e-8);
    }
    this->p_eigsSolver.reset(new QRMethod<double>(this->A, this->tol, 3));
    ASSERT_THROW_MSG(this->p_eigsSolver->ComputeEigs(), ConvergenceError, "Reached maximum number of iterations");

}
