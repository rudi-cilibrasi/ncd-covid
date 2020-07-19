#ifndef __NCD_HELPER_HPP
#define __NCD_HELPER_HPP

#include <string>

class NCDHelper {
    NCDHelper(void);
public:
    static NCDHelper& instance(void);
    double getNCD(const std::string& aCRC, const std::string& bCRC);
};

#endif