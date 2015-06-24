#include "../include/helperfunctions.hpp"

namespace helper{

const std::string getCurrentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

std::string getUppercase(std::string t){
    for(auto i = 0; t[i]; ++i){
        t[i] = toupper(t[i]);
    }
    return t;
}




}
