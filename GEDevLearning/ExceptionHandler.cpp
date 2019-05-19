#include "ExceptionHandler.h"
#include <sstream>

ExceptionHandler::ExceptionHandler(int line, std::string filename)
	:
	_fileName(filename),
	_line(line)
{}


ExceptionHandler::~ExceptionHandler()
{
}

const std::string ExceptionHandler::ExceptionMessage() const
{
	return ExceptionString(ExceptionType(), FileName(), LineNumber(), "STANDARD EXCEPTION");
}

std::string ExceptionHandler::ExceptionString(std::string exceptionType, const std::string fileName, const int lineNumber, const std::string extraInfo) const
{
	std::ostringstream str;
	str << "A " << exceptionType << " has occoured from: " << fileName << ", Line number: " << lineNumber << std::endl << "Extra info: " << extraInfo;

	return str.str();
}
