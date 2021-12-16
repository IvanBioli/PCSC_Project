#ifndef READER_H_
#define READER_H_

#include <iostream>
#include <string>
#include <map>
#include <any>
#include <complex>

/**
 * @class Reader
 * @tparam T Can be <tt>double</tt> or <tt>std::complex<double></tt>. It is the scalar type of which the input matrices
 * and vectors are assumed to be.
 * @brief Abstract class for reading matrices, vectors and scalars.
 * @details The input can be read using the Read() method. To get the map that associates the "name" (i.e. a string) to
 * the corresponding object, use  the GetMap() method.
 *
 * At the moment, only reading from file is implemented.
 * @see FileReader
 *
 * @todo Add derived classes to allow input from command line and other forms of input.
 */
template <typename T> class Reader {
public:
    /**
     * @brief Returns the map.
     */
    std::map<std::string, std::any> GetMap() {return _map;};

    /**
     * @brief Reads the input.
     * @details Pure virtual method to read the input.
     */
    virtual void Read() = 0;

protected:
    /**
     * @details Map that associates a string to the corresponding object.
     *
     * The use of values of type std::any is necessary in order to make the reader able to read objects of different
     * types. Casting the object back to the expected type (looking at the key) is responsibility of the part of the
     * program that uses the map.
     */
    std::map<std::string, std::any> _map;
};

#endif //READER_H_
