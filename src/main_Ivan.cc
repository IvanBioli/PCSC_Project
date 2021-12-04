#include <iostream>
#include <vector>
#include <complex>

#include "AbstractEigs.h"
#include "AbstractPowerMethod.h"
#include "InvPowerMethod.h"
#include "PowerMethod.h"
#include "QRMethod.h"
#include "ShiftPowerMethod.h"
#include "ShiftInvPowerMethod.h"

int main(int argc, char **argv) {
    Eigen::Matrix<double, 4, 4> A;
    A << 5, -2, -1, 0, -2, 5, -1, -1, -1, -1, 4, -1, 0, -1, -1, 5;
    std::cout << A << std::endl;
    Eigen::Vector<double, 4> x0;
    x0 << 1, 1, 1, 1;
    std::cout << x0 << std::endl;
    double tol = 1e-8;
    int itmax = 1000;

    // Power Method
    PowerMethod<double> power(A,tol,itmax,x0);
    std::vector<std::complex<double>> eigs;
    eigs = power.ComputeEigs();
    std::cout << "Power method: " << eigs[0] << std::endl;

    // ShiftPower Method
    double shift = 7;
    ShiftPowerMethod<double> shiftpower(A,tol,itmax,x0, shift);
    eigs = shiftpower.ComputeEigs();
    std::cout << "Shifted power method with shift " << shift << " : " << eigs[0] <<std::endl;

    // InvPowerMethod
    InvPowerMethod<double> invpower(A,tol,itmax,x0);
    eigs = invpower.ComputeEigs();
    std::cout << "Inverse power method: " << eigs[0] <<std::endl;
    invpower.SetMatrix(-A);
    eigs = invpower.ComputeEigs();
    std::cout << "Inverse power method, -A: " << eigs[0] <<std::endl;


    // ShiftInvPowerMethod
    shift = 4;
    ShiftInvPowerMethod<double> shiftinvpower(A,tol,itmax,x0, shift);
    eigs = shiftinvpower.ComputeEigs();
    std::cout << "Inverse power method with shift = " << shift<< " : " << eigs[0] <<std::endl;

    shift = 5.4;
    shiftinvpower.SetShift(shift);
    eigs = shiftinvpower.ComputeEigs();
    std::cout << "Inverse power method with shift = " << shift<< " : " << eigs[0] <<std::endl;

    return 0;
}
