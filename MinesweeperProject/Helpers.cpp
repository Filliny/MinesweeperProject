#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Helpers.h"


/// <summary>
/// Установка текущего цвета консоли
/// </summary>
/// <param name="textColor">цвет текста</param>
/// <param name="backgroundColor">цвет подложки</param>
void consoleSetColors(ConsoleColors textColor, ConsoleColors backgroundColor) {  //setting console colors -устано
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	int color_total = (textColor + (backgroundColor * 16));
	//SetConsoleTextAttribute(hCons, (WORD)((backgroundColor << 4) | textColor));
	SetConsoleTextAttribute(hCons, color_total);
}