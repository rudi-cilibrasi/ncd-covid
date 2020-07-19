#include <datasource.hpp>

using namespace std;

DataSource classifyFAIorFastaFilename(const std::string& filename) {
    if (filename.find("gisaid") == string::npos) {
        return Gurjit;
    }
    return Gisaid;
}

std::string describeDataSource(DataSource ds) {
    if (ds == Gisaid) {
        return "gisaid";
    }
    if (ds == Gurjit) {
        return "gurjit";
    }
    return "unknown";
}