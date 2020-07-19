#include <basicCompressor.hpp>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

using namespace std;

static BasicCompressor *private_instance;

BasicCompressor::BasicCompressor() {

}

BasicCompressor& BasicCompressor::instance(void) {
    if (private_instance == 0) {
        private_instance = new BasicCompressor();
    }
    return *private_instance;
}

uint32_t BasicCompressor::getCompressedSize(const std::string &str) const {
    FILE *fp = fopen("zin", "wb");
    fwrite(str.data(), 1, str.size(), fp);
    fclose(fp);
    system("compressed_size zin >zin.result");
    ifstream inp;
    inp.open("zin.result");
    uint32_t result = -1;
    inp >> result;
    inp.close();
    if (result < 0 || result > 1e5) {
        cerr << "Error getting compressed size with compressed_size zin >zin.result" << "\n";
        exit(1);
    }
    unlink("zin");
    unlink("zin.result");
    return result;
}
