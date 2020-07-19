#include <ncdHelper.hpp>
#include <sequenceCompressor.hpp>
#include <iostream>
#include <taggedSequenceCombination.hpp>

static NCDHelper *private_instance;

using namespace std;

NCDHelper::NCDHelper(void)
{
}

NCDHelper &NCDHelper::instance(void)
{
    if (private_instance == 0)
    {
        private_instance = new NCDHelper();
    }
    return *private_instance;
}

double NCDHelper::getNCD(const std::string &aCRC, const std::string &bCRC)
{
    double ca = SequenceCompressor::instance().getCompressedSizeSingle(aCRC);
    double cb = SequenceCompressor::instance().getCompressedSizeSingle(bCRC);
    double cab = SequenceCompressor::instance().getCompressedSizePair(aCRC, bCRC);
    double minc = (ca < cb) ? ca : cb;
    double maxc = (ca > cb) ? ca : cb;
    double ncd = (cab - minc) / maxc;
    if (ncd > 2.0) {
        cerr << "Error with NCD: " << ncd << "\n";
        cerr << "ca=" << ca << "\n";
        cerr << "cb=" << cb << "\n";
        cerr << "cab=" << cab << "\n";
        cerr << "aCRC=" << aCRC << "\n";
        cerr << "bCRC=" << bCRC << "\n";
        auto tagstr = TaggedSequenceCombinationHelper::formPairTag(aCRC, bCRC);
        cerr << "pairtag=" << tagstr << "\n";
        exit(1);
    }
    return ncd;
}
