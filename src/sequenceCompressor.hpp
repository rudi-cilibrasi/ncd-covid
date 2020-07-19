#ifndef __SEQUENCE_COMPRESSOR_HPP
#define __SEQUENCE_COMPRESSOR_HPP

#include <string>
#include <stddef.h>

class SequenceCompressor {
    SequenceCompressor();
public:
    static SequenceCompressor& instance(void);
    uint32_t getCompressedSizeSingle(const std::string& crc);
    uint32_t getCompressedSizePair(const std::string& crc1, const std::string& crc2);
};

#endif