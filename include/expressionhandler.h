#ifndef EXPRESSIONHANDLER_H
#define EXPRESSIONHANDLER_H

#include <regex>
#include <string>
#include "operator.h"
#include "utils.h"
#include "errors.h"

class Table;

struct CellAdress
{
    std::string column;
    int row;
};

struct Arg
{
    int value;
    CellAdress adress;
    bool isValue;
};

struct UnhandledExpression
{
    int column;
    int row;

    std::vector<Arg> arguments;
    Operator op;
};


class ExpressionHandler
{ 
private:
    const static std::regex _intValidator;
    const static std::regex _expressionValidator;
    const static std::regex _argumentFinder;
    const static std::regex _operatorFinder;
    const static std::regex _rowNumberFinder;
    const static std::regex _columnHeaderFinder;

    Table* _table;
    std::vector<UnhandledExpression> _unhandledExpressions;
private:
    void handleLater(int column, int row, const std::string& expression);
    bool calculateExpression(const UnhandledExpression& expression);
    Arg parseArgument(const std::string& argument);
public:
    ExpressionHandler(Table* table);

    void handleWhenPossible(int column, int row, const std::string& expression);
    void handleAll();
};

#endif // EXPRESSIONHANDLER_H
