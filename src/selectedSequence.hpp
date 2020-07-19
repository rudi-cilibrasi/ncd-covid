#ifndef __SELECTED_SEQUENCE_HPP
#define __SELECTED_SEQUENCE_HPP

#include <string>

class SelectedSequence {
    std::string selectedCRC;
    SelectedSequence(void);
public:
    static SelectedSequence& instance(void);
    std::string getSelectedCRC(void);
};

#endif