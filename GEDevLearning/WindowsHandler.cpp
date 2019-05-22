#include "WindowsHandler.h"
#include <sstream>
#include "resource.h"

Keyboard WindowsHandler::keyboard;
Mouse WindowsHandler::mouse;

std::string WindowsHandler::WindowTitle = "Game Engine";

WindowsHandler::WindowsHandler(HINSTANCE hInstance, int height, int width)
	:
	_width(width),
	_height(height)
{
	instance = hInstance;
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = wndOwnerClassName;
	wc.hIconSm = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));

	RegisterClassEx(&wc);
	CreateAWindow(hInstance, height, width);
}


WindowsHandler::~WindowsHandler()
{
	UnregisterClass(wndOwnerClassName, instance);
	DestroyWindow(hwnd);
}

void WindowsHandler::SetWndowTitle(std::string title)
{
	WindowTitle = "Game Engine" + title;
	if (SetWindowText(hwnd, WindowTitle.c_str()) == 0) {
		throw LAST_EXCEPTION;
	}
}

void WindowsHandler::CreateAWindow(HINSTANCE hInstance, int height, int width)
{
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;

	if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
	{
		throw LAST_EXCEPTION;
	};
	hwnd = CreateWindowEx(
		0, wndOwnerClassName,
		WindowTitle.c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr,
		hInstance, nullptr
	);
	if (hwnd == nullptr)
	{
		throw LAST_EXCEPTION;
	}
	ShowWindow(hwnd, SW_SHOW);
}

LRESULT CALLBACK WindowsHandler::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//RESET KEY UP BOOL IN KEYBOARD
	keyboard.LastUpKeyReset();
	//RESET BUTTON UP BOOL IN MOUSE
	mouse.ButtonStatesReset();

	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(417);
		break;

		// clear keystate/buttonstate when window loses focus to prevent input getting "stuck"
	case WM_KILLFOCUS:
		keyboard.ClearKeyStates();
		mouse.ClearMouse();
		break;

		/*********** KEYBOARD MESSAGES ***********/
	{
	case WM_KEYDOWN:
		// syskey commands need to be handled to track ALT key (VK_MENU) and F10
	case WM_SYSKEYDOWN:
		keyboard.OnKeyPress(wParam, lParam);
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		keyboard.OnKeyRelease(wParam);
		break;
	}
		/*********** END KEYBOARD MESSAGES ***********/

		/*********** MOUSE MESSAGES ***********/
	{
			// LEFT MOUSE BUTTON
	case WM_MOUSEMOVE:
		{
			POINTS pt = MAKEPOINTS(lParam);
			if (GetForegroundWindow() == hwnd) {
				RECT clientRect;
				GetClientRect(hwnd, &clientRect);

				int width = clientRect.right - clientRect.left;
				int height = clientRect.bottom - clientRect.top;

				if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height) {
					mouse.m_Coord.x = static_cast<int>(pt.x);
					mouse.m_Coord.y = static_cast<int>(pt.y);
					if (!mouse.inWnd) {
						SetCapture(hwnd);
						mouse.inWnd = true;
					}
				}
				else {
					if (wParam & (MK_LBUTTON | MK_RBUTTON)) {
						mouse.m_Coord.x = static_cast<int>(pt.x);
						mouse.m_Coord.y = static_cast<int>(pt.y);
					}
					else {
						ReleaseCapture();
						mouse.inWnd = false;
					}
				}
			}
			break;
		}
	case WM_LBUTTONDOWN:
		mouse.leftMB_Down = true;
		break;
	case WM_LBUTTONUP:
		mouse.leftMB_Down = false;
		mouse.leftMB_Up = true;
		mouse.StateChangeTrue();
		break;
		// RIGHT MOUSE BUTTON
	case WM_RBUTTONDOWN:
		mouse.rightMB_Down = true;
		break;
	case WM_RBUTTONUP:
		mouse.rightMB_Down = false;
		mouse.rightMB_Up = true;
		mouse.StateChangeTrue();
		break;
		// MIDDLE MOUSE BUTTON
	case WM_MBUTTONDOWN:
		mouse.middleMB_Down = true;
		break;
	case WM_MBUTTONUP:
		mouse.middleMB_Down = false;
		mouse.middleMB_Up = true;
		mouse.StateChangeTrue();
		break;
	case WM_MOUSEWHEEL:
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
			mouse.scrolledUp = true;
			mouse.StateChangeTrue();
		}
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0) {
			mouse.scrolledDown = true;
			mouse.StateChangeTrue();
		}
		break;
	}
		/*********** END MOUSE MESSAGES ***********/

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

WindowsHandler::Exception::Exception(int line, const char * fileName, HRESULT hr)
	:
	ExceptionHandler(line, fileName),
	_hr(hr)
{}

const std::string WindowsHandler::Exception::TranslateErrorCode(HRESULT hr) const
{
	char* pMsgBuf = nullptr;
	// windows will allocate memory for err string and make our pointer point to it
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);
	// 0 string length returned indicates a failure
	if (nMsgLen == 0)
	{
		return "Unidentified error code";
	}
	// copy error string from windows-allocated buffer to std::string
	std::string errorString = pMsgBuf;
	// free windows buffer
	LocalFree(pMsgBuf);
	return errorString;
}

const std::string WindowsHandler::Exception::ExceptionMessage() const
{
	return ExceptionString(_exceptionType, FileName(), LineNumber(), TranslateErrorCode(_hr));
}
