#ifndef ERRORS_H
#define ERRORS_H

#include <string>

static const std::string FileNotFoundError("File not found.");

static const std::string WrongHeaderFormatError("Wrong header was found.");
static const std::string WrongRowNumberFormatError("Wrong row number was found.");
static const std::string WrongRowSizeError("Wrong row size.");

static const std::string IdenticHeadersError("Identic headers was found.");
static const std::string IdenticRowNumbersError("Identic row numbers was found.");

static const std::string NonexistentHeaderError("Header didn't exist.");
static const std::string NonexistentRowNumberError("Row number didn't exist.");

static const std::string WrongCellDataError("Wrong cell data format.");
static const std::string DivisionByNullError("Division by null was found.");

static const std::string ExpressionLoopError("Seems like there loop in the expressions.");

#endif // ERRORS_H
