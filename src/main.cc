#include <iostream>
#include <complex>
#include <string>
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

    // type must be "real" or "complex"
    if (type != "real" && type != "complex"){
        throw (std::runtime_error("Type must be real or complex"));
    }

    // Reader
    std::unique_ptr<Reader<double>> p_Reader_real;
    std::unique_ptr<Reader<std::complex<double>>> p_Reader_complex;
    if (type == "real"){
        p_Reader_real = std::make_unique<FileReader<double>>(path);
    }
    else { // type == "complex"
        p_Reader_complex = std::make_unique<FileReader<std::complex<double>>>(path);
    }
    // Reading from file
    std::map<std::string, std::any> map;
    if (type == "real") {
        p_Reader_real->Read();
        map = p_Reader_real->GetMap();
    }
    else { // type == "complex"
        p_Reader_complex->Read();
        map = p_Reader_complex->GetMap();
    }


    // Eigenvalues computation
    std::unique_ptr<AbstractEigs<double>> p_eigsSolver_real;
    std::unique_ptr<AbstractEigs<std::complex<double>>> p_eigsSolver_complex;

    // Creating the solver according to the method and the type
    if (method == "power"){
        if (type == "real") {
            p_eigsSolver_real = std::make_unique<PowerMethod<double>>(map);
        }
        else { // type == "complex"
            p_eigsSolver_complex = std::make_unique<PowerMethod<std::complex<double>>>(map);
        }
    }
    else if (method == "invpower"){
        if (type == "real") {
            p_eigsSolver_real = std::make_unique<InvPowerMethod<double>>(map);
        }
        else { // type == "complex"
            p_eigsSolver_complex = std::make_unique<InvPowerMethod<std::complex<double>>>(map);
        }
    }
    else if (method == "shiftpower"){
        if (type == "real") {
            p_eigsSolver_real = std::make_unique<ShiftPowerMethod<double>>(map);
        }
        else { // type == "complex"
            p_eigsSolver_complex = std::make_unique<ShiftPowerMethod<std::complex<double>>>(map);
        }
    }
    else if (method == "shiftinvpower"){
        if (type == "real") {
            p_eigsSolver_real = std::make_unique<ShiftInvPowerMethod<double>>(map);
        }
        else { // type == "complex"
            p_eigsSolver_complex = std::make_unique<ShiftInvPowerMethod<std::complex<double>>>(map);
        }
    }
    else if (method == "qr"){
        if (type == "real") {
            p_eigsSolver_real = std::make_unique<QRMethod<double>>(map);
        }
        else { // type == "complex"
            throw (std::runtime_error("QR Method implemented for real matrices only"));
        }
    }
    else { // The method is not one of the specified ones
        throw (std::runtime_error("Unknown method"));
    }

    // Output the results
    Eigen::Vector<std::complex<double>, -1> eigs;
    if (type == "real") {
        eigs = p_eigsSolver_real->ComputeEigs();
        std::cout << "Initial matrix:" << std::endl;
        std::cout << std::any_cast<Eigen::Matrix<double, -1, -1>>(map["matrix"]) << std::endl;
    }
    else { // type == "complex"
        eigs = p_eigsSolver_complex->ComputeEigs();
        std::cout << "Initial matrix:" << std::endl;
        std::cout << std::any_cast<Eigen::Matrix<std::complex<double>, -1, -1>>(map["matrix"]) << std::endl;
    }
    if (method == "shiftpower" || method == "shiftinvpower") {
        std::cout << "Shift:";
        if (type == "real") {
            std::cout << std::any_cast<double>(map["shift"]) << std::endl;
        }
        else { // type == "complex"
            std::cout << std::any_cast<std::complex<double>>(map["shift"]) << std::endl;
        }
    }
    std::cout << "Eigenvalues computed using " << method << " method" << std::endl;
    std::cout << eigs << std::endl;
}
