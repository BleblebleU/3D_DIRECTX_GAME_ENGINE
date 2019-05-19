#pragma once
#include "SpeedWin.h"
#include "ExceptionHandler.h"

#define LAST_EXCEPTION WindowsHandler::Exception(__LINE__, __FILE__, GetLastError())
#define EXCEPTION(str) WindowsHandler::Exception(__LINE__, __FILE__, str)

class WindowsHandler
{
public:
	class Exception : public ExceptionHandler {
	public:
		Exception(int line, const char* fileName, HRESULT hr);
		const std::string TranslateErrorCode(HRESULT hr) const;
		const std::string ExceptionMessage() const;
		virtual const std::string ExceptionType() const override {
			return _exceptionType;
		}
	private:
		HRESULT _hr;
		const std::string _exceptionType = "WINDOW HANDLER EXCEPTION";
	};
	WindowsHandler(HINSTANCE hInstance, int height, int width);
	~WindowsHandler();

private:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lPARAM);
	void CreateAWindow(HINSTANCE hInstance, int height, int width);

	static constexpr const char* wndOwnerClassName = "GameEngineLearning";
	static constexpr const char* WindowTitle = "GameEngine";
	HINSTANCE instance;
	HWND hwnd;
};

