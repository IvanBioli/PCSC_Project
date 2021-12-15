#include <gtest/gtest.h>
#include <memory>
#include <any>
#include <string>
#include "Eigen/Dense"

#include "Reader.h"
#include "FileReader.h"

#include "Exceptions.h"

template <typename T>
class FileReaderTests : public ::testing::Test {
protected:
    std::unique_ptr<FileReader<T>> p_fileReader;
    std::map<std::string, std::any> map;
    std::string input_path;
    Eigen::Matrix<T, -1, -1> A; // Matrix
    Eigen::Vector<T, -1> x0; // Initial vector
    double tol = 1e-6; // Tolerance
    double maxit = 1000; // Maximum number of iterations
    T shift; // Shift for the shifted methods

    void Initialization();

    void SetUp() override {
        // Initializing the inputs of the methods
        Initialization();
        p_fileReader = std::make_unique<FileReader<T>>(input_path);
    }

    void TearDown() override {}
};

template<>
void FileReaderTests<double>::Initialization() {
    input_path = "../test/test_input_real.txt";
    A.resize(5,5);
    A << 1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        1.2, 0.1, 0.2, 0.3, .4,
        6e-5, 7e-4, 8e-10, 9e10, 10e+1,
        0.6e-10, .7e-5, 3e-4, 9.0e7, 100e-1;
    x0.resize(5);
    x0 << 1, 2, 3, 4, 5;
    shift = 5.2;
}

template<>
void FileReaderTests<std::complex<double>>::Initialization() {
    using c = std::complex<double>;
    input_path = "../test/test_input_complex.txt";
    A.resize(5,5);
    A << c(1,1), c(2,1), c(3,0), c(4,1), c(5,2),
         c(6, 0.1), 7, c(8, 0.3), c(9, 1e-7), 10,
         1.2, 0.1, 0.2, c(0.3,1e5), 1.4,
         c(6e-5, 5e-7), c(0.3, 7e-4), c(8e-10, .3e5), c(9e10, .4), 10e+1,
         0.6e-10, .7e-5, 3e-4, 9.0e7, 100e-1;
    x0.resize(5);
    x0 << c(1,2), c(2,3), c(3,4), c(4,5), c(5,6);
    shift = c(5.1, 1e2);
}

typedef testing::Types<double, std::complex<double>> inputTypes ;
TYPED_TEST_SUITE(FileReaderTests, inputTypes);

TYPED_TEST(FileReaderTests, WrongPath){
    this->p_fileReader->_path = "path/to/nowhere.txt";
    ASSERT_THROW(this->p_fileReader->Read(), FileNotOpen);
}

TYPED_TEST(FileReaderTests, CheckInputs){
    this->p_fileReader->Read();
    this->map = this->p_fileReader->GetMap();
    EXPECT_TRUE(this->A.isApprox(std::any_cast<Eigen::Matrix<TypeParam, -1, -1>>(this->map["matrix"]), 0));
    EXPECT_TRUE(this->x0.isApprox(std::any_cast<Eigen::Vector<TypeParam, -1>>(this->map["x0"]), 0));
    EXPECT_EQ(this->shift,std::any_cast<TypeParam>(this->map["shift"]));
    EXPECT_EQ(this->tol,std::any_cast<double>(this->map["tol"]));
    EXPECT_EQ(this->maxit,std::any_cast<double>(this->map["maxit"]));
}

