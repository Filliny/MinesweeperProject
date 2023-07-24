#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Helpers.h"
#include "Counter.h"

using namespace std;


void CreateField(int size, cell***); //функция создания двухмерного массива поля игры
void fillMines(int size, cell** mas);//функция заполнения поля минами
void freeMemory(int size, cell** mas);//функция очистки памяти занимаемой массивом поля
void printField(int size, cell** mas); //функция вывода всего поля на экран
int openCell(int size, cell** mas, int x, int y); //функция открытия ячейки и рекурсивного открытия соседних ячеек без мин по вертикали и горизонтали
bool checkFlags(int size, cell** mas); //функция проверки открытия всех ячеек без мин (todo - проверка установки флажков на все мины)
bool checkIsDead(int size, cell** mas, int x, int y); //функция проверяет, есть ли в указанной ячейке мина -если нет - вызывает ф-цию открытия ячейки
bool gameEngine(int size, cell** mas);//движок игры , обрабатывает нажатия клавиш и при окончании игры возвращает результат выигрыш\проигрыш true\false
void openField(int size, cell** mas);//функция открытия всех ячеек и вывода на экран открытого поля ( в конце игры)

int main()
{

	printSys();

	cell** mas;
	int size = 20;
	bool run = true;

	while (run) {

		srand(time(NULL));
		CreateField(size, &mas);
		fillMines(size, mas);
		printField(size, mas);

		bool game = gameEngine(size, mas);

		openField(size, mas);

		if (game) {

			cout << "You Win!!! Want to play again? y/n";
		}
		else {
			cout << "You loose!!! Want to play again? y/n";
		}

		char c;
		cin >> c;

		if (c == 'n') run = false;

		freeMemory(size, mas);
	}


}

/// <summary>
/// Движок игры, обрабатывает нажатия клавиш и при окончании игры возвращает результат выигрыш\проигрыш true\false
/// </summary>
/// <param name="size">размер поля игры</param>
/// <param name="mas">двумерный массив поля</param>
/// <returns>выигрыш\проигрыш true\false</returns>
bool gameEngine(int size, cell** mas) {

	bool win = false;//значение для возврата из функции выигрыш\проигрыш true\false

	int x = 0, y = 0; //начальное положение курсора

	mas[x][y].active = true; // делаем начальную ячейку активной

	printField(size, mas);

	int keyCode;
	bool exitGame = false;

	do {  //обработка клавиш игры

		keyCode = _getch();

		switch (keyCode) {
		case 119://up
			if (y - 1 >= 0) {
				mas[y][x].active = false;
				y--;
				mas[y][x].active = true;
			}
			break;

		case 115://down
			if (y + 1 < size) {
				mas[y][x].active = false;
				y++;
				mas[y][x].active = true;
			}
			break;

		case 97://left
			if (x - 1 >= 0) {
				mas[y][x].active = false;
				x--;
				mas[y][x].active = true;
			}
			break;

		case 100://right
			if (x + 1 < size) {
				mas[y][x].active = false;
				x++;
				mas[y][x].active = true;
			}
			break;
		case 13://enter
			if (checkIsDead(size, mas, x, y)) {
				exitGame = true;
			}
			else if (checkFlags(size, mas)) {
				win = true,
					exitGame = true;
			}
			break;
		case 32://space
			mas[y][x].flag = !(mas[y][x].flag);

			if (checkFlags(size, mas)) {
				win = true;
				exitGame = true;
			}
			break;
		case 27: //esc
			exitGame = true;
		default:
			break;
		}

		printField(size, mas);

	} while (!exitGame);

	return win;
}


/// <summary>
/// Функция вывода всего поля на экран
/// </summary>
/// <param name="size">размер поля игры</param>
/// <param name="mas">двумерный массив поля</param>
void printField(int size, cell** mas) {

	consoleSetColors(clWhite, clBlack);
	system("CLS");
	char sign;
	ConsoleColors background = clBlack;
	ConsoleColors text = clWhite;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			//set background установка цвета подложки по состоянию ячейки
			if (mas[i][j].active) {
				background = clYellow;
			}
			else if (mas[i][j].openclose) {
				background = clBlack;
			}
			else {
				background = clBlue;
			}

			//set sign and color  установка цвета текста по состоянию ячейки и знака для вывода
			if (!mas[i][j].openclose && mas[i][j].flag) {
				text = clLightMagenta;
				sign = 'F';
			}
			else if (mas[i][j].openclose && mas[i][j].mine) {//invert first to see bombs
				text = clRed;
				sign = 'B';

			}
			else if (mas[i][j].openclose && mas[i][j].mines_beside > 0) {
				text = clGreen;
				sign = 48 + mas[i][j].mines_beside;
			}
			else {
				text = clBlack;
				if (background == clBlack)
					text = clWhite;
				sign = ' ';
			}

			consoleSetColors(text, background);
			cout << " " << sign << " ";

		}
		cout << endl;
	}
}




/// <summary>
/// Функция создания трехмерного массива поля игры
/// </summary>
/// <param name="size">размер поля игры</param>
/// <param name="mas">указатель на переменную с указателем на игровое поле</param>
void CreateField(int size, cell*** mas) {

	cell** work_mas = new cell * [size];

	for (int i = 0; i < size; i++)
	{
		cell* mas = new cell[size];
		work_mas[i] = mas;
	}

	*mas = work_mas;
}

/// <summary>
/// Функция случайного разбрасывания мин по полю
/// </summary>
/// <param name="size">размер поля игры</param>
/// <param name="mas">двумерный массив поля</param>
void fillMines(int size, cell** mas) {

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{

			mas[i][j].mine = rand() > RAND_MAX * 0.6;
			cout << mas[i][j].mine;

		}

		cout << endl;
	}
}

/// <summary>
/// Функция очистки памяти занимаемой массивом поля
/// </summary>
/// <param name="size">размер поля игры</param>
/// <param name="mas">двумерный массив поля</param>
void freeMemory(int size, cell** mas) {


	for (int j = 0; j < size; j++)
	{
		delete[] mas[j];
	}

	delete[] mas;
}

/// <summary>
/// Функция открытия ячейки по координатам x,y и рекурсивного открытия соседних ячеек без мин по вертикали и горизонтали
/// </summary>
/// <param name="size">размер поля игры</param>
/// <param name="mas">двумерный массив поля</param>
/// <param name="x">индекс столбца</param>
/// <param name="y">индекс строки</param>
/// <returns></returns>
int openCell(int size, cell** mas, int x, int y) {

	if (mas[y][x].mine) return 1;

	if (mas[y][x].openclose == true) return 0;

	mas[y][x].openclose = true;

	if (y - 1 >= 0) {

		if (!(mas[y - 1][x].mine)) {

			openCell(size, mas, x, y - 1);
		}
		else {

			mas[y][x].mines_beside++;
		}
	}

	if (y + 1 < size) {

		if (!(mas[y + 1][x].mine)) {

			openCell(size, mas, x, y + 1);
		}
		else {

			mas[y][x].mines_beside++;
		}
	}


	if (x - 1 >= 0) {

		if (!(mas[y][x - 1].mine)) {

			openCell(size, mas, x - 1, y);
		}
		else {

			mas[y][x].mines_beside++;
		}
	}

	if (x + 1 < size) {

		if (!(mas[y][x + 1].mine)) {

			openCell(size, mas, x + 1, y);
		}
		else {

			mas[y][x].mines_beside++;
		}
	}

	///diagonals

	if (x - 1 >= 0 && y - 1 >= 0) { //left top

		if ((mas[y - 1][x - 1].mine)) {

			mas[y][x].mines_beside++;
		}
	}

	if (x + 1 < size && y - 1 >= 0) { //right top

		if ((mas[y - 1][x + 1].mine)) {

			mas[y][x].mines_beside++;
		}
	}

	if (x - 1 >= 0 && y + 1 < size) { //left bottom

		if ((mas[y + 1][x - 1].mine)) {

			mas[y][x].mines_beside++;
		}
	}

	if (x + 1 < size && y + 1 < size) { //right bottom

		if ((mas[y + 1][x + 1].mine)) {

			mas[y][x].mines_beside++;
		}
	}

	return 0;
}

/// <summary>
/// Функция открытия всех ячеек и вывода на экран открытого поля ( в конце игры)
/// </summary>
/// <param name="size">размер поля игры</param>
/// <param name="mas">двумерный массив поля</param>
void openField(int size, cell** mas) {

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			mas[i][j].openclose = true;
		}
	}

	printField(size, mas);
}

/// <summary>
/// Функция проверки открытия всех ячеек без мин (todo - проверка установки флажков на все мины)
/// </summary>
/// <param name="size">размер поля игры</param>
/// <param name="mas">двумерный массив поля</param>
/// <returns>открыты ли все ячейки без мин true\false</returns>
bool checkFlags(int size, cell** mas) { //do we open all cells not mined?

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{


			if (mas[i][j].mine == mas[i][j].openclose) {

				return false;
			}
		}
	}

	return true;
}

/// <summary>
/// Функция проверяет, есть ли в указанной ячейке мина -если нет - вызывает ф-цию открытия ячейки
/// </summary>
/// <param name="size">размер поля игры</param>
/// <param name="mas">двумерный массив поля</param>
/// <param name="x">индекс столбца</param>
/// <param name="y">индекс строки</param>
/// <returns>есть ли в ячейке мина</returns>
bool checkIsDead(int size, cell** mas, int x, int y) {

	if (mas[y][x].mine) {

		mas[y][x].openclose = true;
		return true;
	}
	else {

		openCell(size, mas, x, y);
		return false;
	}

}