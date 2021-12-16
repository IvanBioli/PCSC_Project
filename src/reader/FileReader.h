#ifndef FILEREADER_H_
#define FILEREADER_H_

#include "Reader.h"
#include "Exceptions.h"
#include <fstream>
#include <Eigen/Dense>

/**
 * @class FileReader
 * @tparam T Can be <tt>double</tt> or <tt>std::complex<double></tt>. It is the scalar type of which the input matrices
 * and vectors are assumed to be.
 * @brief Class for reading matrices, vectors and scalars from file.
 * @details To have more information about the format of the file to be read, see the documentation of the
 * FileReader::Read() method.
 *
 * To have a usage example, let us suppose that a file with the following input format is present at the relative path
 * <tt>../test/test_input_real.txt</tt>
 * \include examples/example_input_real.txt
 *
 * Then, to read input from file:
 * @code{.cpp}
    std::string path = "../test/test_input_real.txt";
    std::map<std::string, std::any> map;
    FileReader<double> fileReader(path);
    fileReader.Read();
    map = fileReader.GetMap();
    std::cout << "matrix:\n" << std::any_cast<Eigen::Matrix<double, -1, -1>>(map["matrix"]) << std::endl;
    std::cout << "x0 (transposed): " << std::any_cast<Eigen::Vector<double, -1>>(map["x0"]).transpose() << std::endl;
    std::cout << "tol: " << std::any_cast<double>(map["tol"]) << std::endl;
    std::cout << "maxit: " << std::any_cast<double>(map["maxit"]) << std::endl;
    std::cout << "shift: " << std::any_cast<double>(map["shift"]) << std::endl;
 * @endcode
 *
 * Output:
 * @code{.unparsed}
    matrix:
         1      2      3      4      5
         6      7      8      9     10
       1.2    0.1    0.2    0.3    0.4
     6e-05 0.0007  8e-10  9e+10    100
     6e-11  7e-06 0.0003  9e+07     10
    x0 (transposed): 1 2 3 4 5
    tol: 1e-06
    maxit: 1000
    shift: 5.2
 * @endcode
 */
template<typename T> class FileReader: public Reader<T> {
public:
    /**
     * @brief Path to the input file.
     */
    std::string _path;

    /**
     * @brief Constructor; sets the path to the input file.
     * @param p path to the input file .
     */
    FileReader(const std::string &p) {_path = p;};

    /**
     * @brief Reads from file.
     */
    void Read() override;

private:

    /**
     * Reads from an object of the std::ifstream class the next input, assuming that it is of type T1 , and returns it.
     * @tparam T1 Expected type of the numeric input.
     * @param read_file Input stream.
     */
    template<typename T1> T1 NumericInput(std::ifstream &read_file);
};

#endif // FILEREADER_H_