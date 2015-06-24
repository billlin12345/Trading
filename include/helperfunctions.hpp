#ifndef HELPERFUNCTIONS_HPP
#define HELPERFUNCTIONS_HPP

#include <string>

namespace helper{

// Gets current date/time, format is YYYY-MM-DD.hppH:mm:ss.
const std::string getCurrentDateTime();

// Returns upper case of a word.
std::string getUppercase(std::string t);

}
#endif // HELPERFUNCTIONS_HPP
