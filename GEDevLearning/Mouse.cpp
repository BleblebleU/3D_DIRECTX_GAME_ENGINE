#include "Mouse.h"

Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

bool Mouse::MouseButtonDown(MouseButton mbType)
{
	switch (mbType) {
	case MB_Left:
		return leftMB_Down;
	case MB_Right:
		return rightMB_Down;
	case MB_Middle:
		return middleMB_Down;
	}
	return false;
}

bool Mouse::MouseButtonUp(MouseButton mbType)
{
	switch (mbType) {
	case MB_Left:
		return leftMB_Down;
	case MB_Right:
		return rightMB_Down;
	case MB_Middle:
		return middleMB_Down;
	}
	return false;
}

bool Mouse::Scrolled()
{
	return scrolledMB_Down;
}

void Mouse::ClearMouse()
{
	leftMB_Down = false;
	rightMB_Down = false;
	middleMB_Down = false;
	scrolledMB_Down = false;
	mb_UpStateChanged = false;
}

void Mouse::ButtonUpReset()
{
	if (mb_UpStateChanged) {
		leftMB_Up = false;
		rightMB_Up = false;
		middleMB_Up = false;
	}
}
