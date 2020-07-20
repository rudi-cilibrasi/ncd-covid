#include <iostream>
#include <fsutil.hpp>
#include <datasource.hpp>
#include <envutil.hpp>
#include <algorithm>
#include <rocksdb/db.h>
#include <textutil.hpp>
#include <sstream>
#include <fstream>
#include <displayName.hpp>

using namespace std;
using namespace rocksdb;

void openDB(const std::string& filename, rocksdb::DB **db)
{
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status =
    rocksdb::DB::Open(options, filename, db);
    if (!status.ok()) {
        cerr << "Cannot open " << filename << "\n";
        exit(1);
    }
}

int main(int argc, char **argv)
{
    rocksdb::DB *db = 0;
    rocksdb::DB *cleanSeqDB = 0;
    rocksdb::DB *nameToCRCDB = 0;
    openDB(getDataFilename("db/rawseq"), &db);
    openDB(getDataFilename("db/cleanseq"), &cleanSeqDB);
    openDB(getDataFilename("db/nameToCRC"), &nameToCRCDB);
    auto sequenceListFilename = getDataFilename("intermediate/sequence-list.txt");
    ofstream sequenceListFile(sequenceListFilename);
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
    map<uint64_t, int> dedup_histo;
    uint32_t gurjit_clean_count = 0, gisaid_clean_count = 0;
    int highest_multiplicity_count = 0;
    uint64_t highest_crc = 0;
    std::string highest_name;
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        auto key = it->key().ToString();
        auto source = classifyFAIorFastaFilename(key);
        auto valueRaw = it->value().ToString();
        auto value = toLowerCase(valueRaw);
        auto kHisto = computeCharacterHistogram(key);
        if (kHisto.find("<") == kHisto.end() ||
            kHisto["<"] != 1) {
                cerr << "Error, key " << key << "\n";
                exit(1);
        }
        auto histo = computeStringSummaryHistogram(value);
        if (histo != "acgt") {
//            cout << "WARNING: rejecting sequence " << key << "\n";
//            cout << "WARNING histo:" << histo << "\n";
//            cout << "WARNING SEQUENCE:" << value << "\n";
            continue;
        }
        if (source == Gurjit) {
            gurjit_clean_count += 1;
        } else {
            gisaid_clean_count += 1;
        }
        auto checksum = computeCRC64WE(value);
        auto checksumString = crcToString(checksum);
        NameAndCRC nac;
        nac.name = key;
        nac.crc = checksumString;
        auto displayName = smartName(nac);
        sequenceListFile << checksumString << ',' << displayName << ',' << key << '\n';
        cleanSeqDB->Put(rocksdb::WriteOptions(), checksumString, value);
        nameToCRCDB->Put(rocksdb::WriteOptions(), key, checksumString);
        if (dedup_histo.find(checksum) == dedup_histo.end()) {
            dedup_histo[checksum] = 0;
        }
        dedup_histo[checksum] += 1;
        if (dedup_histo[checksum] > highest_multiplicity_count) {
            highest_multiplicity_count = dedup_histo[checksum];
            highest_crc = checksum;
            highest_name = key;
        }
    }
    db->Close();
    cleanSeqDB->Close();
    nameToCRCDB->Close();
    auto multiplicitySeqFilename = getDataFilename("intermediate/sequence-counts-by-crc.txt");
    ofstream multiplicitySeq(multiplicitySeqFilename);
    for (auto i = dedup_histo.begin(); i != dedup_histo.end(); ++i) {
        multiplicitySeq << (*i).second << ' ' << (*i).first << '\n';
    }
    auto summaryFilename = getDataFilename("summaries/summary-03-cleaned.txt");
    ofstream summary(summaryFilename);
    summary << "Gurjit total acgt sequences : " << gurjit_clean_count << '\n';
    summary << "Gisaid total acgt sequences : " << gisaid_clean_count << '\n';
    summary << "Most frequent sequence CRC  : " << highest_crc << '\n';
    summary << "Most frequent sequence count: " << highest_multiplicity_count << '\n';
    summary << "Selected sequence name      : " << highest_name << '\n';
    summary << "Selected sequence has CRC   : " << highest_crc << '\n';
    auto selectedCRCFilename = getDataFilename("intermediate/selected-crc.txt");
    ofstream selectedCRC(selectedCRCFilename);
    selectedCRC << highest_crc << '\n';
    return 0;
}