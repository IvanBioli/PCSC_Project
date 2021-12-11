#ifndef FILEREADER_H_
#define FILEREADER_H_

#include "Reader.h"
#include "Exceptions.h"
#include <fstream>
#include <Eigen/Dense>

/**
 * @class
 * TODO: ADD GENERAL DESCRIPTION OF THE FILEREADER CLASS
 */
template<typename T>
class FileReader: public Reader<T> {
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