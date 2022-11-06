#include <Windows.h>
#include "Color.h"

void Color::SetColor(HANDLE hStdOut)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

ConsoleColor Color::GetTextColor(){
	return text;
}

ConsoleColor Color::GetBackgroundColor(){
	return background;
}

void Color::SetTextColor(ConsoleColor _text){
	text = _text;
}

void Color::SetBackgroundColor(ConsoleColor _background){
	background = _background;
}