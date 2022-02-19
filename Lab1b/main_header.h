#pragma once
#include <iostream>
#include <iomanip>
#include <ctime> 
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <chrono>
using namespace std;
template<typename t1, typename t2>
void Enter_check(t1& a, const t2& max, const t2 & min) {
	bool ready = false;
	t1 var1 = max;
	t1 var2 = min;
	string er = "Число не входит в диапазон значений!\n Введите число еще раз: ";
	while (!ready) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{
		string b;

		// функция для ввода строки с пробелами

		getline(cin, b);
		try
		{
			try
			{
				// если дробное
				a = stod(b);
			}
			catch (const std::exception&)
			{
				// в других случаях
				a = stoll(b);
			}
			if (a < var2 || a > var1)  throw er;
			ready = true;
		}
		catch (const string& er)
		{
			cout << er;
		}
		catch (const std::exception&)
		{
			cout << "Замечены сторонние символы!\n Введите число еще раз: ";
		}
	}
}
struct BC {
	string symb;
	int num;
};
struct BigColor {
	BC Black{ "0", 0 };
	BC Blue{ "1", 1 };
	BC Green{ "2", 2 };
	BC Cyan{ "3", 3 };
	BC Red{ "4", 4 };
	BC Magenta{ "5", 5 };
	BC Brown{ "6", 6 };
	BC LightGray{ "7", 7 };
	BC DarkGray{ "8", 8 };
	BC LightBlue{ "9", 9 };
	BC LightGreen{ "A", 10 };
	BC LightCyan{ "B", 11 };
	BC LightRed{ "C", 12 };
	BC LightMagenta{ "D", 13 };
	BC Yellow{ "E", 14 };
	BC White{ "F", 15 };
};
struct MENU {
	BC Back;
	BC Text;
	vector <string> lines;
	vector<int> fillers;
	MENU()
	{
		BigColor Color;
		Back = Color.White;
		Text = Color.Black;
		lines.resize(0);
		fillers.resize(0);
	}
	MENU(vector<string>b1, vector<int>b2)
	{
		BigColor Color;
		Back = Color.White;
		Text = Color.Black;
		lines = b1;
		fillers = b2;
	}
	MENU(vector<string>b1, vector<int>b2, const BC&Text1, const BC& Back1)
	{
		Back = Back1;
		Text = Text1;
		lines = b1;
		fillers = b2;
	}
	~MENU()
	{
		lines.clear();
		fillers.clear();
	}
	int show();
	void color(const string & a);
	void punkt(const string & a, const int & b);

};
