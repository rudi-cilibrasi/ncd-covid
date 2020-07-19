#ifndef __DISTMATRIXWRITER_HPP
#define __DISTMATRIXWRITER_HPP

#include <string>
#include <nameAndCRC.hpp>
#include <map>

class DistMatrixWriter {
    std::map<std::string, NameAndCRC> list;
public:
    DistMatrixWriter(void);
    void addNameAndCRC(const NameAndCRC& nameAndCRC);
    void writeDistanceMatrix(const std::string& shortFilename);
};

#endif