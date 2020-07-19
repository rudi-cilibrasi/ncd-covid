#include <sequenceReader.hpp>
#include <rocksHelper.hpp>
#include <humanMito.hpp>
#include <iostream>
#include <envutil.hpp>

using namespace std;

static SequenceReader *private_instance;

SequenceReader::SequenceReader()
{
    cleanSeqDB = 0;
    RocksHelper::openReaderDB(getDataFilename("db/cleanseq"), &cleanSeqDB);
}

SequenceReader& SequenceReader::instance(void) {
    if (private_instance == 0) {
        private_instance = new SequenceReader();
    }
    return *private_instance;
}

std::string SequenceReader::get_sequence(const std::string &crc)
{
    std::string value;

    if (crc == humanMitoCRCString)
    {
        return humanMitoDNA;
    }
    auto status = cleanSeqDB->Get(rocksdb::ReadOptions(), crc, &value);
    if (!status.ok())
    {
        cerr << "Error, cannot read sequence with crc " << crc << "\n";
        exit(1);
    }
    return value;
}