#include "ShiftPowerMethod.h"

// Constructors
/**
 * @details At least the matrix has to be provided. If the initial vector is not provided, it is set by default to a
 * vector of all ones and a warning is given to the user. If the tolerance, the maximum number of iterations or the
 * shift are not provided, they are set to the default value and a warning is given to the user.
 */
template <typename T>
ShiftPowerMethod<T>::ShiftPowerMethod(std::map<std::string, std::any> &map) : AbstractPowerMethod<T> (map) {
    // Getting and setting the shift
    if (map.count("shift") > 0) {
        T shift;
        try {
            shift = std::any_cast<T>(map["shift"]);
        }
        catch (std::bad_any_cast &e) {
            throw (InitializationError("Unable to cast the shift to the expected type"));
        }
        _shift = shift;
    }
    else { // map.count("shift") == 0
        std::cerr << "WARNING: Unspecified shift. Set by default shift = 0 (Power Method)." << std::endl;
    }
}

// Explicit instantiation for double and std::complex<double>
template class ShiftPowerMethod<double>;
template class ShiftPowerMethod<std::complex<double>>;