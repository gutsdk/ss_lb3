#include <Windows.h>
#include <iostream>
#include "Console.h"
#include "Color.h"
#include "Button.h"

void Console::gotoXY(int x, int y){
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD CursorPosition;

	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void Console::DrawButton(Color color, HANDLE hConsole, Button button)
{
	Console console;
	console.gotoXY(button.GetX(), button.GetY());
	color.SetColor(hConsole);

	for (int i = button.GetY(); i <= button.GetY() + button.GetHeight(); ++i) {
		for (int j = button.GetX(); j <= button.GetX() + button.GetWidth(); j++) {
			console.gotoXY(j, i);
			std::cout << " ";
		}
	}

	int avgX = (2 * button.GetX() + button.GetWidth()) / 2;
	int avgY = (2 * button.GetY() + button.GetHeight()) / 2;

	console.gotoXY(avgX - button.GetText().length() / 2, avgY);
	std::cout << button.GetText();
}
