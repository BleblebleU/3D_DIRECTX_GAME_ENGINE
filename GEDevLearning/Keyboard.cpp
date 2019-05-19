#include "Keyboard.h"

Keyboard::Keyboard()
{
}


Keyboard::~Keyboard()
{
}

const bool Keyboard::OnKeyDown(const unsigned char keyCode) const
{
	return keyDown[keyCode];
}

const bool Keyboard::OnKey(unsigned char keyCode) const
{
	return keyPressed[keyCode];
}

const bool Keyboard::OnKeyUp(const unsigned char keyCode) const
{
	return keyUp[keyCode];
}

void Keyboard::OnKeyPress(const unsigned char wParam, const long lParam)
{
	if (!(lParam & 0x40000000))
	{
		keyDown[wParam] = true;
	}
	else
	{
		keyDown[wParam] = false;
		keyPressed[wParam] = true;
	}
}

void Keyboard::OnKeyRelease(const unsigned char keyCode)
{
	keyPressed[keyCode] = false;
	keyUp[keyCode] = true;
	lastKeyUp = keyCode;
}

void Keyboard::LastUpKeyReset() {
	if (lastKeyUp != -1) {
		keyUp[static_cast<unsigned char>(lastKeyUp)] = false;
		lastKeyUp = -1;
	}
}

void Keyboard::ClearKeyStates()
{
	keyPressed.reset();
	keyDown.reset();
	keyUp.reset();
}
