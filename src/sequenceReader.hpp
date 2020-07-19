#ifndef SEQUENCEREADER_HPP
#define SEQUENCEREADER_HPP

#include <rocksdb/db.h>
#include <string>

class SequenceReader {
    rocksdb::DB *cleanSeqDB;
    SequenceReader();
public:
    static SequenceReader& instance(void);
    std::string get_sequence(const std::string &crc);
};

#endif