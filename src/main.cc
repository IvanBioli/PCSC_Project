#include <iostream>
#include <complex>
#include <string>
#include <exception>

#include "AbstractEigs.h"
#include "AbstractPowerMethod.h"
#include "InvPowerMethod.h"
#include "PowerMethod.h"
#include "QRMethod.h"
#include "ShiftPowerMethod.h"
#include "ShiftInvPowerMethod.h"

#include "Reader.h"
#include "FileReader.h"

int main(int argc, char **argv) {

    std::string method = argv[1];
    std::string path = argv[2];
    std::string type = argv[3];
    /*
    std::string method = "qr";
    std::string path = "C:/Users/ivanb/Documents/GitHub/PCSC_Project/src/real_input.txt";
    std::string type = "real";
    */
    // TODO: USE SMART POINTERS
    // TODO: USE VALGRIND
    // Real case
    AbstractEigs<double>* p_eigsSolver_double;
    FileReader<double> fileReader_double(path);

    // Complex case
    AbstractEigs<std::complex<double>>* p_eigsSolver_complex;
    FileReader<std::complex<double>> fileReader_complex(path);

    // Reading from file
    std::map<std::string, std::any> map;
    if (type == "real") {
        fileReader_double.Read();
        map = fileReader_double.GetMap();
    }
    else if (type == "complex") {
        fileReader_complex.Read();
        map = fileReader_complex.GetMap();
    }
    else { // Type is not complex nor real
        throw (std::runtime_error("Invalid type. Type must be real or complex"));
    }


    // Creating the solver according to the method and the type
    if (method == "power"){
        if (type == "real") {
            p_eigsSolver_double = new PowerMethod<double>(map);
        }
        else { // type == complex
            p_eigsSolver_complex = new PowerMethod<std::complex<double>>(map);
        }
    }
    else if (method == "invpower"){
        if (type == "real") {
            p_eigsSolver_double = new InvPowerMethod<double>(map);
        }
        else { // type == complex
            p_eigsSolver_complex = new InvPowerMethod<std::complex<double>>(map);
        }
    }
    else if (method == "shiftpower"){
        if (type == "real") {
            p_eigsSolver_double = new ShiftPowerMethod<double>(map);
        }
        else { // type == complex
            p_eigsSolver_complex = new ShiftPowerMethod<std::complex<double>>(map);
        }
    }
    else if (method == "shiftinvpower"){
        if (type == "real") {
            p_eigsSolver_double = new ShiftInvPowerMethod<double>(map);
        }
        else { // type == complex
            p_eigsSolver_complex = new ShiftInvPowerMethod<std::complex<double>>(map);
        }
    }
    else if (method == "qr"){
        if (type == "real") {
            p_eigsSolver_double = new QRMethod<double>(map);
        }
        else { // type == complex
            throw (std::runtime_error("QR Method implemented for real matrices only"));
        }
    }
    else { // The method is not one of the specified ones
        throw (std::runtime_error("Unknown method"));
    }


    // Computing the eigenvalues
    Eigen::Vector<std::complex<double>, -1> eigs;
    if (type == "real") {
        eigs = p_eigsSolver_double->ComputeEigs();
    }
    else { // type == complex
        eigs = p_eigsSolver_complex->ComputeEigs();
    }
    std::cout << "Eigenvalues computed using " << method << " method:" << std::endl;
    std::cout << eigs << std::endl;

    // TODO: USE SMART POINTERS
    if (type == "real") {
        delete p_eigsSolver_double;
    }
    else { // type == complex
        delete p_eigsSolver_complex;
    }
}
