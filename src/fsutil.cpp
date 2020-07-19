#include <fsutil.hpp>
#include <envutil.hpp>
#include <filesystem>

using namespace std;

std::vector<std::string> all_fais(void) {
    auto faidir = getDataFilename("incoming");
    std::vector<std::string> result;
    for(auto& p: std::filesystem::recursive_directory_iterator(faidir)) {
        std::string path = p.path();
        if (path.find(".fasta.fai") != string::npos) {
            result.push_back(path);
        }
    }
    return result;
}

std::vector<std::string> all_fasta(void) {
    auto fais = all_fais();
    std::vector<std::string> result;
    for (auto line: fais) {
        auto fasta = line.substr(0, line.size() - 4);
        result.push_back(fasta);
    }
    return result;
}