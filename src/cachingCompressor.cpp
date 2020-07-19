#include <cachingCompressor.hpp>
#include <rocksHelper.hpp>
#include <envutil.hpp>
#include <iostream>
#include <basicCompressor.hpp>
#include <sys/stat.h>

using namespace std;

static CachingCompressor *private_instance;

CachingCompressor& CachingCompressor::instance(void) {
    if (private_instance == 0) {
        private_instance = new CachingCompressor();
    }
    return *private_instance;
}

CachingCompressor::CachingCompressor()
{
    RocksHelper::openReaderWriterDB(getDataFilename("db/compsize"), &compDB);
}

void CachingCompressor::removeTag(const std::string &tag) {
    compDB->Delete(rocksdb::WriteOptions(), tag);
}

bool CachingCompressor::hasTag(const std::string &tag)
{
    string value;
    auto status = compDB->Get(rocksdb::ReadOptions(), tag, &value);
    return status.ok();
}

uint32_t CachingCompressor::getTagSizeFast(const std::string &tag)
{
    string value;
    auto status = compDB->Get(rocksdb::ReadOptions(), tag, &value);
    if (!status.ok())
    {
        cerr << "Error reading fast tag size for " << tag << "\n";
        exit(1);
    }
    uint32_t result;
    memcpy(&result, value.data(), sizeof(result));
    return result;
}

uint32_t CachingCompressor::getTaggedCompressedSize(const TaggedSequenceCombination &inp)
{
    uint32_t result = BasicCompressor::instance().getCompressedSize(inp.seq);
    string k = inp.tag;
    string v((const char *)&result, sizeof(result));
    rocksdb::WriteOptions wo;
    wo.sync = true;
    compDB->Put(wo, k, v);
    struct stat st;
    int rv = stat("/tmp/stop", &st);
    if (rv == 0)
    {
        cerr << "Termination signal received, exiting...\n";
        exit(0);
    }
    return result;
}
