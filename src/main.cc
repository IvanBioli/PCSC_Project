#include <iostream>
#include <complex>
#include <string>
#include <exception>
#include <memory>

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
    // TODO: USE VALGRIND
    // type must be "real" or "complex"
    if (type != "real" && type != "complex"){
        throw (std::runtime_error("type must be real or complex"));
    }

    // Real case
    std::unique_ptr<AbstractEigs<double>> p_eigsSolver_real;
    FileReader<double> fileReader_real(path);

    // Complex case
    std::unique_ptr<AbstractEigs<std::complex<double>>> p_eigsSolver_complex;
    FileReader<std::complex<double>> fileReader_complex(path);

    // Reading from file
    std::map<std::string, std::any> map;
    if (type == "real") {
        fileReader_real.Read();
        map = fileReader_real.GetMap();
    }
    else { // type == "complex"
        fileReader_complex.Read();
        map = fileReader_complex.GetMap();
    }


    // Creating the solver according to the method and the type
    if (method == "power"){
        if (type == "real") {
            p_eigsSolver_real = std::make_unique<PowerMethod<double>>(map);
        }
        else { // type == complex
            p_eigsSolver_complex = std::make_unique<PowerMethod<std::complex<double>>>(map);
        }
    }
    else if (method == "invpower"){
        if (type == "real") {
            p_eigsSolver_real = std::make_unique<InvPowerMethod<double>>(map);
        }
        else { // type == complex
            p_eigsSolver_complex = std::make_unique<InvPowerMethod<std::complex<double>>>(map);
        }
    }
    else if (method == "shiftpower"){
        if (type == "real") {
            p_eigsSolver_real = std::make_unique<ShiftPowerMethod<double>>(map);
        }
        else { // type == complex
            p_eigsSolver_complex = std::make_unique<ShiftPowerMethod<std::complex<double>>>(map);
        }
    }
    else if (method == "shiftinvpower"){
        if (type == "real") {
            p_eigsSolver_real = std::make_unique<ShiftInvPowerMethod<double>>(map);
        }
        else { // type == complex
            p_eigsSolver_complex = std::make_unique<ShiftInvPowerMethod<std::complex<double>>>(map);
        }
    }
    else if (method == "qr"){
        if (type == "real") {
            p_eigsSolver_real = std::make_unique<QRMethod<double>>(map);
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
        eigs = p_eigsSolver_real->ComputeEigs();
    }
    else { // type == complex
        eigs = p_eigsSolver_complex->ComputeEigs();
    }
    std::cout << "Eigenvalues computed using " << method << " method:" << std::endl;
    std::cout << eigs << std::endl;
}
