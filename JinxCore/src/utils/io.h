#ifndef __JINX_UTILS_IO_H
#define __JINX_UTILS_IO_H

#include <iostream>
#include <fstream>
#include <sstream>

namespace jinx { namespace utils {

    std::string getFileContents(std::string fileName);

    template <typename NumericalType>
    std::string numToString(NumericalType number) {
        std::ostringstream s;
        s << number;
        return s.str();
    }

} }

#endif