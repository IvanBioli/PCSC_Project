#ifndef READER_H_
#define READER_H_

#include <iostream>
#include <string>
#include <map>
#include <any>
#include <complex>


template <typename T>
class Reader {
protected:
    std::map<std::string, std::any> _map; // Map from string to any, to store arguments of the solver

public:
    std::map<std::string, std::any> GetMap() {return _map;};
    virtual void Read() = 0;
};

#endif //READER_H_
