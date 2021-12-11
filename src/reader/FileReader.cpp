#include "FileReader.h"

/**
 * @details Reads the input from the file stored at the path specified in FileReader::_path .
 *
 * If it is not able to open the file at the specified path, it throws an exception of type FileNotOpen.
 *
 * It is assumed that the inputs respects the following:
 *  1. Every matrix present in the input file is announced by one line containing only the word <tt>Matrix</tt>,
 *  followed by one line with the key to be associated with the matrix.
 *  Then one line with two integers for the number of rows and the number of columns of the matrix must be present.
 *  The matrix must be entered line by line, with entries divided by spaces and in the format <tt>(a,b)</tt> for
 *  the complex number \f$ a+ib\f$.
 *  2. Every vector present in the input file is announced by one line containing only the word <tt>Vector</tt>,
 *  followed by one line with the key to be associated with the vector.
 *  Then one line with one integer for the number of rows of the vector must be present.
 *  The vector must be entered in a single line, with entries divided by spaces and in the format <tt>(a,b)</tt> for
 *  the complex number \f$ a+ib\f$.
 *  3. Every number of type <tt>T</tt> is announced by one line containing only the word <tt>Type</tt>, followed by one
 *  line with the key to be associated with. The number in then entered in the following line.
 *  4. If not announced by one of the previous keywords, every other input is assumed to be a real number and it is
 *  stored as a <tt>double</tt>. One line contains the key and the following contains the number.
 *
 * Example of input for the real case
 * @include examples/example_input_real.txt
 *
 * Example of input for the complex case
 * @include examples/example_input_complex.txt
 *
 * @todo Add checks on the entries of the matrix effectively given in the file. Check if the number of rows given
 *      corresponds to what indicated in the line after the matrix key. Check if, for each row, the number of entries
 *      given effectively corresponds to the number of columns indicated.
 * @todo Same checks for vectors.
 * @todo In a following stage, automatically extrapolate the number of columns and rows from the input file.
 * @todo Throw specific errors if the numeric input does not correspond to the one expected.
 * @todo Throw error if a key is present without any value or if, viceversa, a value is present without any key.
 * @todo More in general, have a better parser that allows a less restricted input style.
 */
template <typename T>
void FileReader<T>::Read() {
    std::ifstream read_file(this->_path);
    // Checking that the file is open
    if(!read_file.is_open()){
        throw(FileNotOpen("Not able to open input file at " + this->_path));
    }

    // Reading from file line by line
    std::string line;
    while (std::getline(read_file, line)){
        if (line != ""){
            std::any box;
            if (line == "Matrix"){
                // Getting the key to which the matrix is associated
                std::getline(read_file, line);
                // Getting the dimensions of the matrix
                int n, m;
                n = NumericInput<int>(read_file);
                m = NumericInput<int>(read_file);
                // Getting the entries of the matrix
                Eigen::Matrix<T, -1 ,-1> A(n, m);
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < m; ++j){
                        A(i,j) = NumericInput<T>(read_file);
                    }
                }
                box = A;
            }
            else if (line == "Vector"){
                // Getting the key to which the vector is associated
                std::getline(read_file, line);
                // Getting the dimension of the vector
                int n;
                n = NumericInput<int>(read_file);
                // Getting the entries of the vector
                Eigen::Vector<T, -1> vec(n);
                for (int i = 0; i < n; ++i) {
                    vec(i) = NumericInput<T>(read_file);
                }
                box = vec;
            }
            else if (line == "Type"){
                // Getting the key to which the numeric input it associated
                std::getline(read_file, line);
                // Getting the numeric input
                T inputType;
                inputType = NumericInput<T>(read_file);
                box = inputType;
            }
            else{ // We assume in this case to get a scalar that is a double
                // The key to which the numeric input it associated is already stored in the string line, it is needed
                // only to get the numeric input.
                double num;
                num = NumericInput<double>(read_file);
                box = num;
            }
            this->_map[line] = box;
        }
    }
}

template <typename T>
template<typename T1> T1 FileReader<T>::NumericInput(std::ifstream &read_file) {
    T1 num;
    read_file >> num;
    return num;
}

// Explicit instantiation for double and std::complex<double>
template class FileReader<double>;
template class FileReader<std::complex<double>>;