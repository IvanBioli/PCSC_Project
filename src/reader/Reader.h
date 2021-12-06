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
    std::string _path; // Path to the input file
    std::map<std::string, std::any> _map; // Map from string to any, to store arguments of the solver

public:
    Reader();
    Reader(const std::string &p) {_path = p;};
    std::map<std::string, std::any> GetMap() {return _map;};
    virtual void Read() = 0;
};

#endif //READER_H_
