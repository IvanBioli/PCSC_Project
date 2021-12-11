#ifndef READER_H_
#define READER_H_

#include <iostream>
#include <string>
#include <map>
#include <any>
#include <complex>

/**
 * @class
 * TODO: ADD GENERAL DESCRIPTION OF THE READER CLASS
 */
template <typename T>
class Reader {
protected:
    /**
     * @details Map that associates a string to the corresponding object.
     *
     * The use of values of type std::any is necessary in order to make the reader able to read objects of different
     * types. Casting the object back to the expected type (looking at the key) is responsibility of the part of the
     * program that uses the map.
     */
    std::map<std::string, std::any> _map;

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
};

#endif //READER_H_
