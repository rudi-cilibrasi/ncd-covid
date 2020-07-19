#include <textutil.hpp>
extern "C"
{
#include <checksum.h>
}
#include <string.h>
#include <sstream>

using namespace std;

std::string toLowerCase(const std::string &str)
{
    string result;
    for (char c : str)
    {
        c = tolower(c);
        result += c;
    }
    return result;
}

uint64_t computeCRC64WE(const string &str)
{
    return crc_64_we((const unsigned char *)str.data(), str.length());
}

std::map<std::string, uint32_t> computeCharacterHistogram(const std::string &str)
{
    int counts[256];
    memset(counts, 0, sizeof(counts));
    for (char c : str)
    {
        unsigned char us = c;
        counts[us] += 1;
    }
    map<string, uint32_t> result;
    for (int i = 0; i < 256; ++i)
    {
        if (counts[i] == 0)
        {
            continue;
        }
        std::string k;
        char c = i;
        k += c;
        result[k] = counts[i];
    }
    return result;
}

std::string computeStringSummaryHistogram(const std::string &str)
{
    auto vHisto = computeCharacterHistogram(str);
    string histo;
    for (auto i = vHisto.begin(); i != vHisto.end(); ++i)
    {
        auto kc = (*i).first;
        histo += kc;
    }
    return histo;
}

std::string crcToString(uint64_t crc)
{
    ostringstream ost;
    ost << crc;
    return ost.str();
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
        // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    return elems;
}
