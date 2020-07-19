#include <selectedSequence.hpp>
#include <envutil.hpp>
#include <fstream>

static SelectedSequence *private_instance;
using namespace std;

SelectedSequence &SelectedSequence::instance(void)
{
    if (private_instance == 0)
    {
        private_instance = new SelectedSequence();
    }
    return *private_instance;
}

SelectedSequence::SelectedSequence(void)
{
    auto filename = getDataFilename("intermediate/selected-crc.txt");
    ifstream inp(filename);
    getline(inp, selectedCRC);
}

std::string SelectedSequence::getSelectedCRC(void)
{
    return selectedCRC;
}
