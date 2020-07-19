#ifndef __ENTRY_AND_NCD_HPP
#define __ENTRY_AND_NCD_HPP

#include <nameAndCRC.hpp>

struct EntryAndNCD {
    NameAndCRC entry;
    double ncd;
};


class CompareByNCD {
public:
    bool operator()(const EntryAndNCD& a, const EntryAndNCD& b) const {
        return (a.ncd < b.ncd);
    }
};


#endif