#include <iostream>
#include <fsutil.hpp>
#include <datasource.hpp>
#include <envutil.hpp>
#include <algorithm>
#include <rocksdb/db.h>
#include <fastahack/Fasta.h>
#include <map>


using namespace std;

int main(int argc, char **argv)
{
    vector<string> todo = all_fasta();
    string line;
    sort(todo.begin(), todo.end());
    rocksdb::DB *db = 0;
    rocksdb::Options options;
    options.create_if_missing = true;
    options.error_if_exists = true;
    cerr << "About to open db\n";
    auto dbFilename = getDataFilename("db/rawseq");
    std::map<std::string, std::string> done;
    rocksdb::Status status =
        rocksdb::DB::Open(options, dbFilename, &db);
    if (!status.ok()) {
        cerr << "Cannot open " << dbFilename << "\n";
        exit(1);
    }
    cerr << "Opened db\n";
    int removeCharLen = getDataFilename("incoming/").size();
    int seqCount = 0;
    for (auto line: todo) {
        FastaReference fref;
        fref.open(line);
        auto shortName = line.substr(removeCharLen);
        FastaIndex &findex = *fref.index;
        for (auto seqName: findex.sequenceNames) {
            string seq = fref.getSequence(seqName);
            string key = shortName + "<" + seqName ;
            if (seqName == "hCoV-19") {
                continue;
            }
            string value = seq;
            cout << key << "\n";
            if (done.find(key) != done.end()) {
                cout << "WARNING: sequence found with same key: " << key << "\n";
                if (done[key] != value) {
                    cout << "WARNING: sequence data does not match for key " << key << "\n";
                }
            }
            db->Put(rocksdb::WriteOptions(), key, value);
            done[key] = value;
            seqCount += 1;
        }
    }
    db->Close();
    auto summaryFilename = getDataFilename("summaries/summary-02-import.txt");
    ofstream summary(summaryFilename);
    summary << "Imported " << done.size() << " sequences total into raw sequence database\n";
    return 0;
}