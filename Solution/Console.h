#pragma once
class Color;
class Button;
class Console{
public:
	void gotoXY(int, int);

	void DrawButton(Color, HANDLE, Button);
};
