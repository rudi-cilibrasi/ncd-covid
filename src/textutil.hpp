#ifndef __TEXTUTIL_HPP
#define __TEXTUTIL_HPP

#include <string>
#include <stddef.h>
#include <map>
#include <vector>

std::string toLowerCase(const std::string& str);
uint64_t computeCRC64WE(const std::string& str);
std::map<std::string, uint32_t> computeCharacterHistogram(const std::string& str);
std::string computeStringSummaryHistogram(const std::string& str);
std::string crcToString(uint64_t crc);
std::vector<std::string> split(const std::string &s, char delim);

#endif