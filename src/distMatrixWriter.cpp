#include <distMatrixWriter.hpp>
#include <envutil.hpp>
#include <fstream>
#include <displayName.hpp>
#include <ncdHelper.hpp>

using namespace std;

static std::string forMatrix(const std::string& name) {
    std::string result;
    for (char c: name) {
        if (c == '/') {
            c = '_';
        }
        result.push_back(c);
    }
    return result;
}

DistMatrixWriter::DistMatrixWriter(void) {
}

void DistMatrixWriter::addNameAndCRC(const NameAndCRC& nameAndCRC) {
    list[nameAndCRC.crc] = nameAndCRC;
}

void DistMatrixWriter::writeDistanceMatrix(const std::string& shortFilename) {
    NCDHelper& ncdHelper = NCDHelper::instance();
    auto filename = getDataFilename("intermediate/" + shortFilename);
    ofstream f(filename);
    for (auto i = list.begin(); i != list.end(); ++i) {
        auto ancd = (*i).second;
        f << forMatrix(smartName(ancd));
        for (auto j = list.begin(); j != list.end(); ++j) {
            auto bncd = (*j).second;
            auto ncd = ncdHelper.getNCD(ancd.crc, bncd.crc);
            f << ' ' << ncd;
        }
        f << '\n';
    }
    f.close();
}