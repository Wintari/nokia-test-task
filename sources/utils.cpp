#include "utils.h"

std::vector<std::string> split(const std::string& str, const std::string& delimiters){
    std::vector<std::string> parts;
    size_t start = 0, end = 0;
    while (end < str.size()) {
        end = start;
        while (end < str.size() && (delimiters.find(str[end]) == std::string::npos)) {
            end++;
        }

        if(end - start != 0)
        {
            parts.push_back(std::string(str, start, end-start));
        }
        else
        {
              parts.push_back("");
        }

        start = end + 1;
    }

    return parts;
}
