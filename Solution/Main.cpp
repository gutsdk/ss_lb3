#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <locale.h>
#include "Console.h"
#include "Button.h"
#include "Color.h"

#define BUFFSIZE 256
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30
#define BTN_WIDTH 10
#define BTN_HEIGHT 3
#define BTN_COUNT 6

HANDLE hStdin;
DWORD fdwSaveOldMode;
STARTUPINFO si;
PROCESS_INFORMATION pi;

VOID ErrorExit(LPCSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

BOOL exitFg, processFg;
Color color;
Console console;
Button btnList[BTN_COUNT];
std::vector<std::string> txtList = {"C + C", "C + ASM", "ASM + C", "ASM + ASM", "LAB2", "EXIT"};

int main() {
	setlocale(LC_ALL, "ru");
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[BUFFSIZE];
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	exitFg = 0;
	processFg = 0;

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");

	color.SetTextColor(ConsoleColor::LightCyan);
	color.SetBackgroundColor(ConsoleColor::LightCyan);
	color.SetColor(hConsole);

	for (int i = 0; i <= SCREEN_WIDTH; ++i) {
		for (int j = 0; j <= SCREEN_HEIGHT; j++) {
			console.gotoXY(i, j);
			std::cout << " ";
		}
	}

	int count = 0;
	for (auto s : txtList) {
		auto btn = Button(BTN_WIDTH, BTN_HEIGHT, s);
		btnList[count] = btn;
		count++;
	}

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	Color btnColor;
	btnColor.SetBackgroundColor(ConsoleColor::LightRed);
	btnColor.SetTextColor(ConsoleColor::White);

	btnList[0].SetX(20);
	btnList[0].SetY(5);
	console.DrawButton(btnColor, hConsole, btnList[0]);

	btnList[1].SetX(80);
	btnList[1].SetY(5);
	console.DrawButton(btnColor, hConsole, btnList[1]);

	btnList[2].SetX(20);
	btnList[2].SetY(12);
	console.DrawButton(btnColor, hConsole, btnList[2]);

	btnList[3].SetX(80);
	btnList[3].SetY(12);
	console.DrawButton(btnColor, hConsole, btnList[3]);

	btnList[4].SetX(20);
	btnList[4].SetY(20);
	console.DrawButton(btnColor, hConsole, btnList[4]);

	btnList[5].SetX(80);
	btnList[5].SetY(20);
	console.DrawButton(btnColor, hConsole, btnList[5]);

	while (!exitFg) {
		if (!ReadConsoleInput(
			hStdin,     
			irInBuf,    
			BUFFSIZE,   
			&cNumRead)) 
			ErrorExit("ReadConsoleInput");

		for (i = 0; i < cNumRead; i++) {
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: 
				processFg = 1;
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;
			case MOUSE_EVENT: 
				processFg = 1;
				MouseEventProc(irInBuf[i].Event.MouseEvent);
				break;
			case WINDOW_BUFFER_SIZE_EVENT: 
				ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;
			case FOCUS_EVENT:  
			case MENU_EVENT:   
				break;
			default:
				ErrorExit("Unknown event type");
				break;
			}
			if (processFg) {
				FlushConsoleInputBuffer(hStdin);
			}
			if (exitFg)
				break;
		}
	}
	SetConsoleMode(hStdin, fdwSaveOldMode);
	return 0;
}

VOID ErrorExit(LPCSTR lpszMessage) {
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
	ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker) {
	if (ker.bKeyDown) {
		switch (ker.uChar.AsciiChar) {
		case '1':
			CreateProcess(L"../exec/C-C.exe",
				NULL,
				NULL,
				NULL,
				TRUE,
				CREATE_NEW_CONSOLE,
				NULL,
				NULL,
				&si,
				&pi);
			break;
		case '2':
			CreateProcess(L"../exec/C-Asm.exe",
				NULL,
				NULL,
				NULL,
				TRUE,
				CREATE_NEW_CONSOLE,
				NULL,
				NULL,
				&si,
				&pi);
			break;
		case '3':
			CreateProcess(L"../exec/Asm-C.exe",
				NULL,
				NULL,
				NULL,
				TRUE,
				CREATE_NEW_CONSOLE,
				NULL,
				NULL,
				&si,
				&pi);
			break;
		case '4':
			CreateProcess(L"../exec/Asm-Asm.exe",
				NULL,
				NULL,
				NULL,
				TRUE,
				CREATE_NEW_CONSOLE,
				NULL,
				NULL,
				&si,
				&pi);
			break;
		case '5':
			CreateProcess(L"../exec/SPO2.exe",
				NULL,
				NULL,
				NULL,
				TRUE,
				CREATE_NEW_CONSOLE,
				NULL,
				NULL,
				&si,
				&pi);
			break;
		case '6':
			exitFg = 1;
			break;
		}
	}
	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer) {
	int x = mer.dwMousePosition.X;
	int y = mer.dwMousePosition.Y;

	if (((x >= btnList[0].GetX() && x <= btnList[0].GetX() + BTN_WIDTH) && (y >= btnList[0].GetY() && y <= btnList[0].GetY() + BTN_HEIGHT)) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
		CreateProcess(L"../exec/C-C.exe",
			NULL,
			NULL,
			NULL,
			TRUE,
			CREATE_NEW_CONSOLE,
			NULL,
			NULL,
			&si,
			&pi);
	}
	if (((x >= btnList[1].GetX() && x <= btnList[1].GetX() + BTN_WIDTH) && (y >= btnList[1].GetY() && y <= btnList[1].GetY() + BTN_HEIGHT)) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
		CreateProcess(L"../exec/C-Asm.exe",
			NULL,
			NULL,
			NULL,
			TRUE,
			CREATE_NEW_CONSOLE,
			NULL,
			NULL,
			&si,
			&pi);
	}
	if (((x >= btnList[2].GetX() && x <= btnList[2].GetX() + BTN_WIDTH) && (y >= btnList[2].GetY() && y <= btnList[2].GetY() + BTN_HEIGHT)) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
		CreateProcess(L"../exec/Asm-C.exe",
			NULL,
			NULL,
			NULL,
			TRUE,
			CREATE_NEW_CONSOLE,
			NULL,
			NULL,
			&si,
			&pi);
	}
	if (((x >= btnList[3].GetX() && x <= btnList[3].GetX() + BTN_WIDTH) && (y >= btnList[3].GetY() && y <= btnList[3].GetY() + BTN_HEIGHT)) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
		CreateProcess(L"../exec/Asm-Asm.exe",
			NULL,
			NULL,
			NULL,
			TRUE,
			CREATE_NEW_CONSOLE,
			NULL,
			NULL,
			&si,
			&pi);
	}
	if (((x >= btnList[4].GetX() && x <= btnList[4].GetX() + BTN_WIDTH) && (y >= btnList[4].GetY() && y <= btnList[4].GetY() + BTN_HEIGHT)) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
		CreateProcess(L"../exec/SPO2.exe",
			NULL,
			NULL,
			NULL,
			TRUE,
			CREATE_NEW_CONSOLE,
			NULL,
			NULL,
			&si,
			&pi);
	}
	if (((x >= btnList[5].GetX() && x <= btnList[5].GetX() + BTN_WIDTH) && (y >= btnList[5].GetY() && y <= btnList[5].GetY() + BTN_HEIGHT)) && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
		exitFg = 1;
		return;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr) {
	/*gotoXY(0, 0);
	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);*/
}