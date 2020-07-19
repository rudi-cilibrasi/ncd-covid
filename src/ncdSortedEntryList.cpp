#include <ncdSortedEntryList.hpp>
#include <selectedSequence.hpp>
#include <ncdHelper.hpp>
#include <algorithm>

using namespace std;

NCDSortedEntryList::NCDSortedEntryList(void): sorted(false) {
   skSelected = SelectedSequence::instance().getSelectedCRC();
}

void NCDSortedEntryList::addEntry(const NameAndCRC& nameAndCRC) {
    sorted = false;
    EntryAndNCD entry;
    NCDHelper& ncdHelper = NCDHelper::instance();
    entry.entry = nameAndCRC;
    entry.ncd = ncdHelper.getNCD(skSelected, entry.entry.crc);
    entries.push_back(entry);
}

const std::vector<EntryAndNCD>& NCDSortedEntryList::getSortedList(void) {
    if (!sorted) {
        sort(entries.begin(), entries.end(), CompareByNCD());
        sorted = true;
    }
    return entries;
}

const std::vector<EntryAndNCD> NCDSortedEntryList::getTruncatedSortedList(uint32_t howMany) {
    getSortedList();
    if (howMany >= entries.size()) {
        return entries;
    }
    std::vector<EntryAndNCD> result(entries.begin(), entries.begin() + howMany);
    return result;
}
