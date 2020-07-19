#include <treeMaker.hpp>

using namespace std;
void TreeMaker::makeTreeFile(const std::string& inputFilename, const std::string& outFilename) {
    string firstCmd = "docker run --rm --name ncd-app-instance -v ~/var/covid-exp/intermediate:/expdir  ncd bash -c 'cd /expdir && maketree " + inputFilename + "'";
    system(firstCmd.c_str());
    string secondCmd = "cd ~/var/covid-exp/intermediate && ruby ~/src/paul-covid/tree_converter/convert_tree.rb >" + outFilename;
    system(secondCmd.c_str());
    string thirdCmd = "rm -f ~/var/covid-exp/intermediate/treefile.dot";
//    system(thirdCmd.c_str());
}

void TreeMaker::makeDiagramTree(const std::string& inputFilename, const std::string& outFilename) {
    string cmd = "cp ~/var/covid-exp/intermediate/"+inputFilename + " intree && rm -f plotfile && (echo \"F\\nHershey\\nY\\n\" | /usr/lib/phylip/bin/drawgram) && mv plotfile ~/var/covid-exp/intermediate/" + outFilename + " && rm intree";
    system(cmd.c_str());
}