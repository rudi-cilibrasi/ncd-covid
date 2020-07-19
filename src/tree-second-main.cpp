#include <iostream>
#include <selectedSequence.hpp>
#include <sequenceReader.hpp>
#include <ncdHelper.hpp>
#include <set>
#include <vector>
#include <entryAndNCD.hpp>
#include <seqNameHelper.hpp>
#include <ncdSortedEntryList.hpp>
#include <humanMito.hpp>
#include <datasource.hpp>
#include <distMatrixWriter.hpp>
#include <treeMaker.hpp>

using namespace std;

int main(int argc, char **argv)
{
    const int experiment_size = 24;
    auto skSelected = SelectedSequence::instance().getSelectedCRC();
    NCDHelper &ncdHelper = NCDHelper::instance();
    set<string> donelist;
    vector<EntryAndNCD> processed;
    NameAndCRC snac;
    SeqNameHelper &snh = SeqNameHelper::instance();
    NCDSortedEntryList sortedList;
    for (auto it = snh.nameToCRC.begin(); it != snh.nameToCRC.end(); ++it)
    {
        auto k = (*it).first;
        auto crc = (*it).second;
        if (donelist.find(crc) != donelist.end())
        {
            continue;
        }
        NameAndCRC nameAndCRC;
        nameAndCRC.crc = crc;
        nameAndCRC.name = k;
        if (classifyFAIorFastaFilename(nameAndCRC.name) == Gurjit) {
            continue;
        }
        sortedList.addEntry(nameAndCRC);
        donelist.insert(nameAndCRC.crc);
    }
    donelist.clear();
    DistMatrixWriter distMatrixWriter;

    auto elist = sortedList.getTruncatedSortedList(12);
    EntryAndNCD human;
    human.entry = humanNameAndCRC;
    human.ncd = ncdHelper.getNCD(skSelected, humanMitoCRCString);
    elist.insert(elist.begin(), human);
    for (auto e: elist) {
        distMatrixWriter.addNameAndCRC(e.entry);
        donelist.insert(e.entry.crc);
    }
    for (auto it = snh.nameToCRC.begin(); it != snh.nameToCRC.end(); ++it)
    {
        auto k = (*it).first;
        auto crc = (*it).second;
        NameAndCRC nameAndCRC;
        nameAndCRC.crc = crc;
        nameAndCRC.name = k;
        if (classifyFAIorFastaFilename(nameAndCRC.name) == Gurjit) {
            continue;
        }
        if (donelist.find(crc) != donelist.end())
        {
            continue;
        }
        if (nameAndCRC.name.find("/2017") != string::npos ||
            nameAndCRC.name.find("/2018") != string::npos ||
            nameAndCRC.name.find("/2019") != string::npos) {
            distMatrixWriter.addNameAndCRC(nameAndCRC);
            donelist.insert(crc);
        }
    }

    vector<NameAndCRC> list;
    sortedList = NCDSortedEntryList();
    for (auto it = snh.nameToCRC.begin(); it != snh.nameToCRC.end(); ++it)
    {
        auto k = (*it).first;
        auto crc = (*it).second;
        if (donelist.find(crc) != donelist.end())
        {
            continue;
        }
        NameAndCRC nameAndCRC;
        nameAndCRC.crc = crc;
        nameAndCRC.name = k;
        if (classifyFAIorFastaFilename(nameAndCRC.name) == Gisaid) {
            continue;
        }
        sortedList.addEntry(nameAndCRC);
    }
    for (auto e: sortedList.getTruncatedSortedList(12)) {
        if (donelist.find(e.entry.crc) == donelist.end()) {
            distMatrixWriter.addNameAndCRC(e.entry);
            donelist.insert(e.entry.crc);
        }
    }

    std::string distMatrixName = "secondtreematrix.txt";
    distMatrixWriter.writeDistanceMatrix(distMatrixName);
    cerr << "Wrote " << distMatrixName << '\n';
    TreeMaker::makeTreeFile(distMatrixName, "secondtree.newick");
    TreeMaker::makeDiagramTree("secondtree.newick", "secondtree.ps");
    return 0;
}