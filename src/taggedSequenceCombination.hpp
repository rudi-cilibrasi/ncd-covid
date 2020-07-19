#ifndef __TAGGEDSEQUENCECOMBINATION_HPP
#define __TAGGEDSEQUENCECOMBINATION_HPP

#include <stddef.h>
#include <string>

struct TaggedSequenceCombination {
    std::string tag;
    std::string seq;
};

class TaggedSequenceCombinationHelper {
public:
    static std::string formSingleTag(const std::string& crc);
    static std::string formPairTag(const std::string& crc1, const std::string& crc2);
    static TaggedSequenceCombination formSingle(const std::string& crc);
    static TaggedSequenceCombination formPair(const std::string& crc1, const std::string& crc2);
};

#endif