#pragma once
#include <string>

class ExceptionHandler
{
public:

	virtual std::string ExceptionString(std::string exceptionType,
										const std::string fileName, 
										const int lineNumber, 
										const std::string extraInfo) const;

	ExceptionHandler(int line, std::string filename);
	~ExceptionHandler();
	virtual const std::string ExceptionMessage() const;
	virtual const std::string ExceptionType() const {
		return _exceptionType;
	}
	virtual const std::string FileName() const {
		return _fileName;
	}
	virtual const int LineNumber() const {
		return _line;
	}
protected:
	const std::string _exceptionType;
	const std::string _fileName;
	const int _line;
};

