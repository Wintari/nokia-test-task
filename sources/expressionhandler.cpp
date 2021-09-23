#include "expressionhandler.h"
#include "table.h"

const std::regex ExpressionHandler::_intValidator = std::regex("^\\s*" + intRegExp + + "\\s*$");
const std::regex ExpressionHandler::_expressionValidator = std::regex("^\\s*=" + argumentRegExp + "\\s*" +
                                                                     operatorRegExp + "\\s*" + argumentRegExp
                                                                      + "\\s*$");
const std::regex ExpressionHandler::_argumentFinder = std::regex(argumentRegExp);
const std::regex ExpressionHandler::_operatorFinder = std::regex(operatorRegExp);
const std::regex ExpressionHandler::_columnHeaderFinder = std::regex(cellHeaderRegExp);
const std::regex ExpressionHandler::_rowNumberFinder = std::regex(cellNumberRegExp);

ExpressionHandler::ExpressionHandler(Table* table)
{
    _table = table;
}

void ExpressionHandler::handleWhenPossible(int column, int row, const std::string &expression)
{
    if(std::regex_match(expression, _intValidator))
    {
        _table->setValueDirectly(column, row, std::stoi(expression));
    }
    else if(std::regex_match(expression, _expressionValidator))
    {
        handleLater(column, row, expression);
    }
    else
    {
        throw WrongCellDataError;
    }
}

void ExpressionHandler::handleLater(int column, int row, const std::string& expression)
{
    std::vector<Arg> arguments;

    const std::vector<std::smatch> matches{
        std::sregex_iterator{expression.begin(), expression.end(), _argumentFinder},
        std::sregex_iterator{}
    };
    {
        for(const auto& arg : matches){
            arguments.push_back(parseArgument(arg.str()));
        }
    }

    std::smatch match;
    std::regex_search(expression, match, _operatorFinder);
    std::string op = match[0];

    _unhandledExpressions.push_back({column, row, arguments, Operator(op)});
}

Arg ExpressionHandler::parseArgument(const std::string& argument)
{
    if(std::regex_match(argument, _intValidator))
    {
        return {std::stoi(argument), CellAdress(), true};
    }
    else
    {
        std::smatch match;

        std::regex_search(argument, match, _columnHeaderFinder);
        std::string column = match[0];

        std::regex_search(argument, match, _rowNumberFinder);
        int row = std::stoi(match[0]);

        return {0, {column, row}, false};
    }
}

void ExpressionHandler::handleAll()
{
    int handledOnThisIteration = -1;

    while(handledOnThisIteration != 0)
    {
        std::vector<UnhandledExpression> handleOnNextIteration;
        handledOnThisIteration = 0;

        for(const auto& expression : _unhandledExpressions)
        {
            if(calculateExpression(expression))
            {
                handledOnThisIteration += 1;
            }
            else
            {
                handleOnNextIteration.push_back(expression);
            }
        }

        std::swap(_unhandledExpressions, handleOnNextIteration);
    }

    if(!_unhandledExpressions.empty())
    {
        throw ExpressionLoopError;
    }
}

bool ExpressionHandler::calculateExpression(const UnhandledExpression& expression)
{
    std::vector<int> argValues;
    for(const auto& arg: expression.arguments)
    {
        if(arg.isValue)
        {
            argValues.push_back(arg.value);
        }
        else
        {
            auto cell =_table->getCell(arg.adress.column, arg.adress.row);
            if(cell.isValid())
            {
                argValues.push_back(cell.getValue());
            }
            else
            {
                return false;
            }
        }
    }

    _table->setValueDirectly(expression.column, expression.row,
                             expression.op(argValues));
    return true;
}
