#ifndef UTILS_H
#define UTILS_H

#include <string>

const static std::string intRegExp("([+-]?[1-9]\\d*|0)");
const static std::string cellAdressRegExp("(([a-z]|[A-Z])+([1-9]\\d*))");
const static std::string argumentRegExp("(" + intRegExp + "|" + cellAdressRegExp + ")");
const static std::string operatorRegExp("(\\s*(\\+|-|\\*|\\/)\\s*)");

#endif // UTILS_H
