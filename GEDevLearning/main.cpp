#include "WindowsHandler.h"
#include <sstream>
//const std::string originalTitle = "Hello First Window";
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg) {
//	case WM_CLOSE:
//		PostQuitMessage(0417);
//		break;
//	case WM_KEYDOWN:
//		if(wParam == 'F')
//		{
//			SetWindowTextA(hwnd, "Respects");
//			break;
//		}
//		if (wParam == 'D') {
//			SetWindowTextA(hwnd, "dText");
//			break;
//		}
//	case WM_KEYUP:
//		{
//			SetWindowTextA(hwnd, originalTitle.c_str());
//			break; 
//		}
//	case WM_CHAR:
//
//		if (wParam == 'L') {
//			SetWindowTextA(hwnd, "you took an L");
//			break;
//		}
//		if (wParam != 'f' && wParam != 'd') {
//			static std::string title;
//			title.push_back((char)wParam);
//			SetWindowTextA(hwnd, title.c_str());
//			break;
//		}
//	case WM_LBUTTONDOWN:
//		{
//			const POINTS pt = MAKEPOINTS(lParam);
//			std::stringstream oss; 
//			oss << "(" << (pt.x) << "," << pt.y << ")";
//			SetWindowTextA(hwnd, oss.str().c_str());
//			break;
//		}
//	}
//	return DefWindowProc(hwnd, msg, wParam, lParam);
//}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{
	try {
		WindowsHandler window(hInstance, 480, 620);

		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (window.keyboard.OnKeyUp(K_A)) {
				MessageBox(nullptr, "THE A KEY WAS PRESSED", "The Key enun is working", MB_OK | MB_ICONEXCLAMATION);
			}
			if (window.mouse.MouseButtonDown(MB_Middle)) {
				std::stringstream oss;
				oss << "THE Left Mouse Button WAS PRESSED AT: (" << window.mouse.MouseX() << ", " << window.mouse.MouseY() << ")";
				MessageBox(nullptr, oss.str().c_str(), "The MB enun is working", MB_OK | MB_ICONEXCLAMATION);
			}
		}

		if (gResult == -1) {
			return -1;
		}

		return msg.wParam;
	}
	catch(const ExceptionHandler& e)
	{
		MessageBox(nullptr, e.ExceptionMessage().c_str(), e.ExceptionType().c_str(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}