#ifndef __NCD_SORTED_ENTRY_LIST
#define __NCD_SORTED_ENTRY_LIST

#include <entryAndNCD.hpp>
#include <vector>
#include <string>

class NCDSortedEntryList {
    bool sorted;
    std::string skSelected;
    std::vector<EntryAndNCD> entries;
public:
    NCDSortedEntryList(void);
    void addEntry(const NameAndCRC& nameAndCRC);
    const std::vector<EntryAndNCD>& getSortedList(void);
    const std::vector<EntryAndNCD> getTruncatedSortedList(uint32_t howMany);
};

#endif