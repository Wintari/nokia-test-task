#include "operator.h"


int add(const std::vector<int>& values)
{
    return values[0] + values[1];
}

int substract(const std::vector<int>& values)
{
    return values[0] - values[1];
}

int multiply(const std::vector<int>& values)
{
    return values[0] * values[1];
}


int divide(const std::vector<int>& values)
{
    if(values[1] == 0)
    {
        throw DivisionByNullError;
    }

    return values[0] / values[1];
}


const std::unordered_map<std::string, int(*)(const std::vector<int>&)> Operator::_operations = {
                                                                         {"+", add},
                                                                         {"-", substract},
                                                                         {"*", multiply},
                                                                         {"/", divide}
        };

Operator::Operator(const std::string& op)
{
    _operation = _operations.find(op)->second;
}

int Operator::operator()(const std::vector<int>& values) const
{
    return _operation(values);
}


