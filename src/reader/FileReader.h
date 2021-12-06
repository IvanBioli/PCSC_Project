#ifndef FILEREADER_H_
#define FILEREADER_H_

#include "Reader.h"
#include <fstream>

template<typename T>
class FileReader: public Reader<T> {
public:
    FileReader(const std::string &p) : Reader<T>(p) {};
    void Read() override;

private:
    template<typename T1> T1 NumericInput(const std::ifstream &if_stream);
};

#endif // FILEREADER_H_