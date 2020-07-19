#ifndef __CACHING_COMPRESSOR_HPP
#define __CACHING_COMPRESSOR_HPP

#include <rocksdb/db.h>
#include <taggedSequenceCombination.hpp>
#include <stddef.h>

class CachingCompressor {
    rocksdb::DB *compDB;
    CachingCompressor();
    public:
    static CachingCompressor& instance();
    bool hasTag(const std::string &tag);
    uint32_t getTagSizeFast(const std::string& tag);
    uint32_t getTaggedCompressedSize(const TaggedSequenceCombination& inp);
    void removeTag(const std::string &tag);
};

#endif