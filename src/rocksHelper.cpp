#include <rocksHelper.hpp>
#include <iostream>

using namespace std;

void RocksHelper::openReaderDB(const std::string &filename, rocksdb::DB **db)
{
    rocksdb::Options options;
    rocksdb::Status status =
        rocksdb::DB::Open(options, filename, db);
    if (!status.ok())
    {
        cerr << "Cannot open " << filename << "\n";
        exit(1);
    }
}

void RocksHelper::openReaderWriterDB(const std::string &filename, rocksdb::DB **db)
{
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status =
        rocksdb::DB::Open(options, filename, db);
    if (!status.ok())
    {
        cerr << "Cannot open " << filename << "\n";
        exit(1);
    }
}