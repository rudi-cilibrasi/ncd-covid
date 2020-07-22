#include <iostream>
#include <selectedSequence.hpp>
#include <sequenceReader.hpp>
#include <ncdHelper.hpp>
#include <set>
#include <vector>
#include <entryAndNCD.hpp>
#include <seqNameHelper.hpp>
#include <displayName.hpp>
#include <envutil.hpp>
#include <fstream>
#include <cachingCompressor.hpp>
#include <datasource.hpp>
#include <ncdSortedEntryList.hpp>

using namespace std;

int main(int argc, char **argv) {
    auto skSelected = SelectedSequence::instance().getSelectedCRC();
    NCDHelper& ncdHelper = NCDHelper::instance();
    NCDSortedEntryList sortedList;
    auto ncd = ncdHelper.getNCD(skSelected, skSelected);
    set<string> donelist;
    vector<EntryAndNCD> processed;
    NameAndCRC snac;
    SeqNameHelper &snh = SeqNameHelper::instance();
    double worstNCD=0.0f;
    string worstCRC;
    string worstName;
    NameAndCRC worstNameAndCRC;
    string worstSequence;
    int retainedGisaidCount = 0;
    double retainedGisaidSum = 0.0f;
    // CachingCompressor::instance().removeTag("15428970192809444366/15292229339988812524");
    for (auto it = snh.nameToCRC.begin(); it != snh.nameToCRC.end(); ++it) {
        auto k = (*it).first;
        auto crc = (*it).second;
        if (donelist.find(crc) != donelist.end()) {
            continue;
        }
        auto ncd = ncdHelper.getNCD(skSelected, crc);
        NameAndCRC nameAndCRC;
        nameAndCRC.name = k;
        nameAndCRC.crc = crc;
        if (k.find("MN908947") != string::npos || nameAndCRC.crc == skSelected) {
            sortedList.addEntry(nameAndCRC);
            donelist.insert(crc);
        }
    }
    for (auto it = snh.nameToCRC.begin(); it != snh.nameToCRC.end(); ++it) {
        auto k = (*it).first;
        auto crc = (*it).second;
        if (donelist.find(crc) != donelist.end()) {
            continue;
        }
        auto ncd = ncdHelper.getNCD(skSelected, crc);
        NameAndCRC nameAndCRC;
        nameAndCRC.name = k;
        nameAndCRC.crc = crc;
        cout << k << '\n';
        cout << crc << ',' << ncd << ',' << smartName(nameAndCRC) << '\n';
        if (nameAndCRC.name.find("hCoV") == string::npos) {
            sortedList.addEntry(nameAndCRC);
            donelist.insert(crc);
        }
        if (k.find("/2017") == string::npos &&
            k.find("/2018") == string::npos &&
            k.find("/2019") == string::npos && classifyFAIorFastaFilename(k) == Gisaid &&
            k.find("hCoV") != string::npos &&
            k.find("hCoV-19/bat") == string::npos
            ) {
            auto curncd = ncdHelper.getNCD(skSelected, crc);
            if (curncd >= worstNCD) {
                worstNCD = curncd;
                worstCRC = crc;
                worstNameAndCRC = nameAndCRC;
            }
            retainedGisaidCount += 1;
            retainedGisaidSum += curncd;
        }
    }
    auto filename = getDataFilename("summaries/summary-04-worst.txt");
    auto outfile = ofstream(filename);
    outfile << "Worst NCD: " << worstNCD << "\n";
    outfile << "Worst CRC: " << worstCRC << "\n";
    outfile << "Worst Name: " << worstNameAndCRC.name << "\n";
    outfile << "Total retained sequences: " << retainedGisaidCount << '\n';
    outfile << "Average NCD retained seq: " << retainedGisaidSum/retainedGisaidCount << '\n';
    outfile << "Display Worst Name: " << smartName(worstNameAndCRC) << "\n";
//    outfile << "Worst sequence: " << worstSequence << "\n";
    filename = getDataFilename("summaries/summary-05-github-uri.txt");
    outfile.close();
    outfile = ofstream(filename);
    outfile << "Github source code URI: https://github.com/rudi-cilibrasi/ncd-covid\n";
    outfile.close();
    filename = getDataFilename("intermediate/table-60-sorted.txt");
    outfile = ofstream(filename);
    for (auto entry : sortedList.getTruncatedSortedList(60)) {
        outfile << entry.ncd << '&' << smartName(entry.entry) << "\\\\\n";
    }
    outfile.close();
    return 0;
}
