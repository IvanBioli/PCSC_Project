#ifndef FILEREADER_H_
#define FILEREADER_H_

#include "Reader.h"
#include "Exceptions.h"
#include <fstream>
#include <Eigen/Dense>

template<typename T>
class FileReader: public Reader<T> {
public:
    std::string _path; // Path to the input file
    FileReader(const std::string &p) {_path = p;};
    void Read() override;

private:
    template<typename T1> T1 NumericInput(std::ifstream &read_file);
};

#endif // FILEREADER_H_