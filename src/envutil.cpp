#include <envutil.hpp>
#include <string.h>

std::string getDataDir(void) {
    const char *top = getenv("TOPDATADIR");
    if (top == 0 || strlen(top) == 0)
        return "/home/rudi/var/covid-exp";
    return top;
}

std::string getDataFilename(const std::string& sub) {
    return getDataDir() + "/" + sub;
}