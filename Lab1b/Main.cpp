﻿#include "List_r.h"

int main() {
	BigColor Color;
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title List");//задание описания окна консоли
	system("mode con cols=78 lines=50");//задание размеров окна консоли
	string back_txt = "color " + Color.White.symb + Color.Black.symb;
	system(back_txt.c_str());
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);//получение хендла
	CONSOLE_CURSOR_INFO cursor = { 100,false };//число от 1 до 100 размер курсора в процентах; false\true - видимость
	SetConsoleCursorInfo(hCons, &cursor);
	List<float>::use();
}