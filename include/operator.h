#ifndef OPERATOR_H
#define OPERATOR_H

#include <vector>
#include <string>
#include <unordered_map>

#include "errors.h"

class Operator
{
private:
    const static std::unordered_map<std::string, int(*)(const std::vector<int>&)> _operations;

    int (*_operation)(const std::vector<int>&);
public:
    Operator(const std::string& op);

    int operator()(const std::vector<int>& values) const;
};

#endif // OPERATOR_H
