#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

const static std::string intRegExp("([+-]?[1-9]\\d*|0)");
const static std::string cellHeaderRegExp("([a-z]|[A-Z])+");
const static std::string cellNumberRegExp("([1-9]\\d*)");
const static std::string cellAdressRegExp(cellHeaderRegExp + cellNumberRegExp);
const static std::string argumentRegExp("(" + intRegExp + "|" + cellAdressRegExp + ")");
const static std::string operatorRegExp("((\\+|-|\\*|\\/))");

std::vector<std::string> split(const std::string& str, const std::string& delimiters);

#endif // UTILS_H
