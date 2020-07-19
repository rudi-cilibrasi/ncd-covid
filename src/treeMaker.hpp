#ifndef __TREEMAKER_HPP
#define __TREEMAKER_HPP

#include <string>

class TreeMaker {
public:
    static void makeTreeFile(const std::string& inputFilename, const std::string& outFilename);
    static void makeDiagramTree(const std::string& inputFilename, const std::string& outFilename);
};

#endif