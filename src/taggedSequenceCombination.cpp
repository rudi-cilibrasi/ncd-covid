#include <taggedSequenceCombination.hpp>
#include <sequenceReader.hpp>

std::string TaggedSequenceCombinationHelper::formSingleTag(const std::string& crc) {
    return crc;
}

std::string TaggedSequenceCombinationHelper::formPairTag(const std::string& crc1, const std::string& crc2) {
    return crc1 + "/" + crc2;
}

TaggedSequenceCombination TaggedSequenceCombinationHelper::formSingle(const std::string& crc) {
    TaggedSequenceCombination result;
    result.tag = formSingleTag(crc);
    result.seq = SequenceReader::instance().get_sequence(crc);
    return result;
}

TaggedSequenceCombination TaggedSequenceCombinationHelper::formPair(const std::string& crc1, const std::string& crc2) {
    TaggedSequenceCombination result;
    result.tag = formPairTag(crc1, crc2);
    result.seq = SequenceReader::instance().get_sequence(crc1) + SequenceReader::instance().get_sequence(crc2);
    return result;
}