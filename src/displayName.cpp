#include <string>
#include <displayName.hpp>
#include <textutil.hpp>
#include <datasource.hpp>
#include <humanMito.hpp>
#include <iostream>
#include <selectedSequence.hpp>
using namespace std;

static std::string smartNameGurjit(const NameAndCRC& nameAndCRC) {
    auto partsBig = split(nameAndCRC.name, '<');
    if (partsBig.size() < 2) {
        return nameAndCRC.name;
    }
    auto bigFilename = partsBig[0];
    auto accession = partsBig[1];
    auto filenameParts = split(bigFilename, '/');
    auto lastFilename = filenameParts[filenameParts.size()-1];
    auto goodFilename = split(lastFilename, '.')[0];
    return accession + "_" + goodFilename;
}

static std::string smartNameGisaid(const NameAndCRC& nameAndCRC) {
    auto partsBig = split(nameAndCRC.name, '<');
    if (partsBig.size() < 2) {
        return nameAndCRC.name;
    }
//    std::cout << "name is " << nameAndCRC.name << '\n';
    auto combinedFields = partsBig[1];
    auto parts = split(combinedFields, '|');
    auto filename = parts[0];
    auto goodFilename = filename.substr(5);
//    std::cout << "Combined Fields is " << combinedFields << '\n';
    std::string accession;
    if (parts.size() > 1) {
        accession = parts[1];
    }
    return accession + "_" + goodFilename;
}

static std::string skSelected;
std::string smartName(const NameAndCRC& nameAndCRC) {
    if (nameAndCRC.crc == humanMitoCRCString) {
        return "humanMito";
    }
    if (nameAndCRC.crc == "488174185055826200") {
        return "MN908947.3_alt._SARS_CoV_2";
    }
    if (nameAndCRC.name.find("MG772933.1") != string::npos) {
        return "MG772933.1_bat_SL_CoVZC45";
    }
    if (nameAndCRC.name.find("MG772934.1") != string::npos) {
        return "MG772934.1_bat_SL_CoVZXC21";
    }
    if (skSelected.empty()) {
        skSelected = SelectedSequence::instance().getSelectedCRC();
    }
    if (nameAndCRC.crc == skSelected) {
        return "selected_SARS_CoV_2_EPI_ISL_471246";
    }
    if (classifyFAIorFastaFilename(nameAndCRC.name) == Gisaid) {
//        cerr << "Using GISAID naming scheme\n";
        return smartNameGisaid(nameAndCRC);
    }
//    cerr << "USING Gurjit naming scheme\n";
    return smartNameGurjit(nameAndCRC);
}
