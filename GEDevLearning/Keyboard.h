#pragma once

#include <bitset>
#include <map>

enum Keys {
	K_SHIFT = 0x10
	, K_CTRL = 0x11, K_ESC = 0x1B, K_SPACE = 0x20

	, K_LEFTARROW = 0x25
	, K_UPARROW, K_RIGHTARROW, K_DOWNARRORW

	, K_A = 0x41
	, K_B, K_C, K_D, K_E, K_F, K_G, K_H, K_I, K_J, K_K, K_L, K_M, K_N, K_O, K_P, K_Q, K_R, K_S, K_T, K_U, K_V, K_W, K_X, K_Y, K_Z

	, K_Tp_0 = 0x30
	, K_Tp_1, K_Tp_2, K_Tp_3, K_Tp_4, K_Tp_5, K_Tp_6, K_Tp_7, K_Tp_8, K_Tp_9

	, K_NumPd_0 = 0x60
	, K_NumPd_1, K_NumPd_2, K_NumPd_3, K_NumPd_4, K_NumPd_5, K_NumPd_6, K_NumPd_7, K_NumPd_8, K_NumPd_9

	, K_F1 = 0x70
	, K_F2, K_F3, K_F4, K_F5, K_F6, K_F7, K_F8, K_F9, K_F10, K_F11, K_F12
};

class Keyboard
{
	friend class WindowsHandler;

public:
	Keyboard();
	~Keyboard();
	const bool OnKeyDown(const unsigned char keyCode) const;
	const bool OnKey(const unsigned char keyCode) const;
	const bool OnKeyUp(const unsigned char keyCode) const;
protected:
	void OnKeyPress(const unsigned char keyCode, const long lParam);
	void OnKeyRelease(const unsigned char keyCode);
	void ClearKeyStates();
	void LastUpKeyReset();
private:
	static constexpr unsigned int nKEYS = 256u;

	std::bitset<nKEYS> keyPressed;
	std::bitset<nKEYS> keyDown;
	std::bitset<nKEYS> keyUp;

	int lastKeyUp;
};