#include "main_header.h"

int MENU::show()
{
	// обарботка разницы размеров
	if (fillers.size() != lines.size())
		return -1;

	// работа с курсором
	// _________________
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 100,false };
	SetConsoleCursorInfo(hCons, &cursor);
	// _________________

	// объявление переменных
	int choice;
	int pos = 1;

	// системная строка цветов консоли
	string back_txt = "color " + Back.symb + Text.symb;

	// бесконечный цикл
	for (;;)
	{
		// задание параметров фона и текста консоли
		system(back_txt.c_str());
		// цикл вывода пунктов меню
		for (int iter = 0; iter < fillers.size(); iter++) {
			if (iter != pos) {
				cout << setw(fillers[iter] + lines[iter].length()) << lines[iter] << endl;
			}
			else punkt(lines[pos] , fillers[iter]);
		}
		// получение введенной клавишы
		choice = _getch();
		choice = choice == 224 ? _getch() : choice;// down , up
		system("cls");
		// обработка клавиш
		if(choice == 13)return pos; // enter
		else if (choice == 27)return 0; // esc
		else if (choice == 72) pos = pos == 1 ? lines.size() - 1 : pos - 1;// up
		else if (choice == 80) pos = pos == lines.size() - 1 ? 1 : pos + 1;// down
	}
}
// функция окрашивающая принимаемую строку в серый
void MENU::color(const string& a) {
	// 1 - фон, 2 - текст
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	BigColor col;
	SetConsoleTextAttribute(hConsole, (WORD)((col.Black.num << 4) | col.White.num));
	cout << a;
	SetConsoleTextAttribute(hConsole, (WORD)((Back.num << 4) | Text.num));
}
// функция которая показывает какую строку выбрали
void MENU::punkt(const string& a, const int & b) {
	cout << setw(b) << "--> ";
	color(a);
	cout << endl;
}
