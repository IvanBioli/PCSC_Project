#include "FileReader.h"

template <typename T>
void FileReader<T>::Read() {
    throw(std::runtime_error("Not implemented"));
}

// Needed for linking
template class FileReader<double>;
template class FileReader<std::complex<double>>;