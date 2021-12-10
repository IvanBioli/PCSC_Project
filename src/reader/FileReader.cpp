#include "FileReader.h"

template <typename T>
void FileReader<T>::Read() {
    std::ifstream read_file(this->_path);
    if(!read_file.is_open()){
        throw(FileNotOpen("Not able to open input file in " + this->_path));
    }

    std::string line;
    while (std::getline(read_file, line)){
        if (line != ""){
            std::any box;
            if (line == "matrix"){
                int n, m;
                n = NumericInput<int>(read_file);
                m = NumericInput<int>(read_file);
                Eigen::Matrix<T, -1 ,-1> A(n, m);
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < m; ++j){
                        A(i,j) = NumericInput<T>(read_file);
                    }
                }
                box = A;
            }
            else if (line == "vector"){
                int n;
                std::getline(read_file, line);
                n = NumericInput<int>(read_file);
                Eigen::Vector<T, -1> vec(n);
                for (int i = 0; i < n; ++i) {
                    vec(i) = NumericInput<T>(read_file);
                }
                box = vec;
            }
            else if (line == "shift"){
                T shift;
                shift = NumericInput<T>(read_file);
                box = shift;
            }
            else{ // We assume in this case to get a scalar that is a double
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

// Needed for linking
template class FileReader<double>;
template class FileReader<std::complex<double>>;