#pragma once
class Button{
private:
	int width;
	int height;
	std::string text;

	int X;
	int Y;
public:
	int GetHeight();
	void SetHeight(int);

	int GetWidth();
	void SetWidth(int);

	std::string GetText();
	void SetText(std::string);

	int GetX();
	void SetX(int);

	int GetY();
	void SetY(int);

	Button();
	Button(int, int, std::string);
};