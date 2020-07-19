#include <textutil.hpp>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    string teststr = "TEST";
    cout << teststr << "\n";
    cout << toLowerCase(teststr) << "\n";
    cout << computeCRC64WE(teststr) << "\n";
    cout << computeStringSummaryHistogram(teststr) << "\n";
    return 0;
}