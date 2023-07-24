#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>


struct cell {

	int mines_beside = 0; //0
	boolean openclose = false;
	boolean flag = false;
	boolean active = false;
	boolean mine = false; //false

};


enum floors //Уровни трехмерного массива 
{
	mines_beside,
	openclose,
	flag,
	active,
	mine
};

enum ConsoleColors {      // LRGB LRGB    Light Reg Green Blue  - консольные цвета
	clBlack = 0  // 0000 0000
	, clBlue = 1  // 0000 0001
	, clGreen = 2  // 0000 0010
	, clCyan = 3  // 0000 0011
	, clRed = 4  // 0000 0100
	, clMagenta = 5  // 0000 0101
	, clBrown = 6  // 0000 0110
	, clLightGrey = 7  // 0000 0111
	, clDarkGrey = 8  // 0000 1000 
	, clLightBlue = 9  // 0000 1001
	, clLightGreen = 10  // 0000 1010
	, clLightCyan = 11  // 0000 1011
	, clLightRed = 12  // 0000 1100
	, clLightMagenta = 13  // 0000 1101
	, clYellow = 14  // 0000 1110
	, clWhite = 15  // 0000 1111 
};

void consoleSetColors(ConsoleColors textColor, ConsoleColors backgroundColor);//функция установки цвета вывода следующего символа (цвет текста, цвет подложки)

