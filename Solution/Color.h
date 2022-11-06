#pragma once
static enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

class Color{
private:
	ConsoleColor text;
	ConsoleColor background;
public:
	void SetColor(HANDLE);

	ConsoleColor GetTextColor();
	ConsoleColor GetBackgroundColor();

	void SetTextColor(ConsoleColor);
	void SetBackgroundColor(ConsoleColor);
};