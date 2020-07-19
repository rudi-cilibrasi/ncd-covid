#ifndef __BASIC_COMPRESSOR_HPP
#define __BASIC_COMPRESSOR_HPP

#include <stddef.h>
#include <string>

class BasicCompressor {
    BasicCompressor();
public:
    static BasicCompressor& instance(void);
    uint32_t getCompressedSize(const std::string &str) const;
};

#endif