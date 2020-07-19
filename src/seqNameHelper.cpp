#include <seqNameHelper.hpp>
#include <rocksHelper.hpp>
#include <humanMito.hpp>
#include <envutil.hpp>
#include <iostream>


static SeqNameHelper *private_instance;

SeqNameHelper& SeqNameHelper::instance(void) {
    if (private_instance == 0) {
        private_instance = new SeqNameHelper();
    }
    return *private_instance;
}

SeqNameHelper::SeqNameHelper() {
    nameToCRCDB = 0;
    nameToCRC[humanNameAndCRC.name] = humanNameAndCRC.crc;
    RocksHelper::openReaderDB(getDataFilename("db/nameToCRC"), &nameToCRCDB);
    rocksdb::Iterator* it = nameToCRCDB->NewIterator(rocksdb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        auto key = it->key().ToString();
        auto value = it->value().ToString();
        std::cerr << "key is " << key << '\n';
        nameToCRC[key] = value;
        crcToAName[value] = key;
    }
    nameToCRCDB->Close();
}
