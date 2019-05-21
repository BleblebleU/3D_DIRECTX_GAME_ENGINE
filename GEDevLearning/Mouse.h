#pragma once

enum MouseButton {
	MB_Left,
	MB_Right,
	MB_Middle
};

class Mouse
{
	friend class WindowsHandler;
public:
	Mouse();
	~Mouse();
	bool MouseButtonDown(MouseButton mbType);
	bool MouseButtonUp(MouseButton mbType);
	bool Scrolled();

	int MouseX() {
		return m_Coord.x;
	}
	int MouseY() {
		return m_Coord.y;
	}

private:
	struct MouseCoord {
		int x;
		int y;
	};

private:
	void ClearMouse();
	void UpStateTrue() {
		mb_UpStateChanged = true;
	}
	void ButtonUpReset();
private:
	MouseCoord m_Coord;

	bool leftMB_Down = false;
	bool rightMB_Down = false;
	bool middleMB_Down = false;
	bool scrolledMB_Down = false;

	bool leftMB_Up = false;
	bool rightMB_Up = false;
	bool middleMB_Up = false;
	bool scrolledMB_Up = false;

	bool mb_UpStateChanged = false;
};

