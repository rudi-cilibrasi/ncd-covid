#ifndef __SEQNAMEHELPER_HPP
#define __SEQNAMEHELPER_HPP

#include <rocksdb/db.h>
#include <map>
#include <string>

class SeqNameHelper {
    rocksdb::DB *nameToCRCDB;
    SeqNameHelper();
public:
    static SeqNameHelper& instance(void);
    std::map<std::string, std::string> nameToCRC;
    std::map<std::string, std::string> crcToAName;
};

#endif