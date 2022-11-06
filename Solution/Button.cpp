#include <Windows.h>
#include <iostream>
#include "Button.h"

Button::Button(){
	width = 0;
	height = 0;
	text = "";
}

Button::Button(int _width, int _height, std::string _text) {
	width = _width;
	height = _height;
	text = _text;
}

int Button::GetHeight(){
	return height;
}

void Button::SetHeight(int _heigth){
	height = _heigth;
}

int Button::GetWidth(){
	return width;
}

void Button::SetWidth(int _width){
	width = _width;
}

std::string Button::GetText(){
	return text;
}

void Button::SetText(std::string _text){
	text = _text;
}

int Button::GetX(){
	return X;
}

void Button::SetX(int _X){
	X = _X;
}

int Button::GetY(){
	return Y;
}

void Button::SetY(int _Y){
	Y = _Y;
}
