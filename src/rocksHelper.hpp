#ifndef __ROCKSHELPER_HPP
#define __ROCKSHELPER_HPP

#include <string>
#include <rocksdb/db.h>

class RocksHelper {
public:
    static void openReaderDB(const std::string& filename, rocksdb::DB **db);
    static void openReaderWriterDB(const std::string& filename, rocksdb::DB **db);
};

#endif
