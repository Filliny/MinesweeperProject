#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Helpers.h"


/// <summary>
/// ��������� �������� ����� �������
/// </summary>
/// <param name="textColor">���� ������</param>
/// <param name="backgroundColor">���� ��������</param>
void consoleSetColors(ConsoleColors textColor, ConsoleColors backgroundColor) {  //setting console colors -������
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	int color_total = (textColor + (backgroundColor * 16));
	//SetConsoleTextAttribute(hCons, (WORD)((backgroundColor << 4) | textColor));
	SetConsoleTextAttribute(hCons, color_total);
}