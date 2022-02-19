﻿#pragma once
#include "main_header.h"
template<class T>
class List
{
	// список методов к выполнению

	/*
	   "1 - Добавление",
	   "2 - Удаление",
	   "3 - Эдит",
	   "4 - Печать",
	   "5 - Поиск",
	   "6 - Сортировка",
	   "7 - Достать элемент из файла",
	   "8 - Положить элемент в файл",
	   "9 - Сохранение таблицы",
	   "10 - Открытие таблицы",
	   "11 - О разработчике",
	   "12 - Выход"
	*/



	//////////////////////////////////////////////////
    //       переменные управляющего списка         //
    //////////////////////////////////////////////////

	/* начало списка "голова", "корень" */
	static List* head;
	/* конец списка "хвост" */
	static List* tail;
	/* буферный указатель (для удобного пользования) */
	static List* buf;
	/* количество экземпляров */
	static int count;
	/* расположение для сохранения и открытия */
	static string Fpath;

	//////////////////////////////////////////////////




    /////////////////////////////////////////////////////
	//       переменные одного элемента списка         //
	/////////////////////////////////////////////////////

	/* следующий элемент */
	List* next;
	/* предыдущий */
	List* prev;
		/* номер по порядку */
	int index;
	/* информация */
    T num;
	
	/////////////////////////////////////////////////////




	///////////////////////////////////////////
    //       перегруженные операторы         //
    ///////////////////////////////////////////


	/* сеттер */
	void operator()(const T& a);
	/* оператор поиска по индексу */
	List<T>*& operator[](const int& ind); 
	/* оператор присвоения */
	List<T>& operator=(const List<T>& other);
	/* операторы сравнения */
	bool operator >(List<T>* other) { return num > other->num; }
	bool operator <(List<T>* other) { return num < other->num; }
	bool operator >=(List<T>* other) { return num >= other->num; }
	bool operator <=(List<T>* other) { return num <= other->num; }
	bool operator ==(List<T>* other) { 
		if (index == other->index && num == other->num)
			return true;
		else return false;
	}
	bool operator !=(List<T>* other) { return index != other->index || num != other->num; }
	/* оператор ввода/вывода в/на консоль */
	istream& operator>>(istream & in);
	ostream& operator<< (ostream& out);
	/* операторы вывода из файла */
	template <class V>
	friend ifstream& operator>> (ifstream& in, List<V>* a);
	
    ///////////////////////////////////////////




	///////////////////////////////////////////////////////
	//       методы для работы с размером списка         //
	///////////////////////////////////////////////////////

	/* добавление элемента в любое место списка */
	List<T>* add(List <T>*& head0, List <T>*& tail0);
	/* удаление из любого места в списке*/
	List<T>* del(List <T>*& head0, List <T>*& tail0);
	/* метод добавления в заданное место списка */
	static void add(const int& pos, const int& kol, const int& meth);
	/* метод удаления из заданного места списка*/
	static void del(const int& pos, const int& kol);	
	/* очистка списка */
	static bool clear();
	/* метод который заполняет информацией один элемент списка(из файла) */
	void randomFromFile();// случайный из файла
	
	///////////////////////////////////////////////////////




	/////////////////////////////////////
	//       методы "проверки"         //
	/////////////////////////////////////

	/* проверка правильности пути файла */
	static bool pathCheck()
    /* проверка пути, введен ли он, и есть ли там расширение */
	{ return Fpath == "" ? false :(Fpath.find(".txt")!= string:: npos? true:false); }
	/* проверка всех индексов в списке (и автоисправление)*/
	static void indxCheck();
	/* проверка на наличие элементов */
	static bool empty() {
		if (head == nullptr)cout << "Список пуст! Функция недоступна!" << endl;
		return head == nullptr;
	}
	/* проверка сохранения в файле */
	static bool saved();

	/////////////////////////////////////

	


	/////////////////////////////////////////////////////////////////
	//       методы для работы с выводом(и с файлами тоже)         //
	/////////////////////////////////////////////////////////////////

	/* вывод шапки в файл */
	static ofstream& fileSh(ofstream& out);
	/* внутренний метод печати */
	static void print(const bool& all_l, const bool& strght);
	/* вывод шапки в консоль */
	static void consoleSh();
	/* метод рассчета отступов */
	int col_count(const int& a, const int& b);

	/////////////////////////////////////////////////////////////////




	//////////////////////////////////////
	//       сортировка и свапы         //
	//////////////////////////////////////

	/* внутренний метод сортировки */
	static void sort(const bool& orderAZ = true);
	/* свап по значению */
	static void swap(List<T>* a, List<T>* b);
	/* свап по указателю */
	static void swapPointers(List<T>*&a, List<T>*& b);

	//////////////////////////////////////




	//////////////////////////
	//       другое         //
	//////////////////////////

	/* установка пути */
	static void setPath(const string& path = "");
	/* возврат элемента по значению */
	List<T>& ret_el() { return *this; }
	/* проверка ввода */
	template<typename t1, typename t2>
	friend void Enter_check(t1& a, const t2& max, const t2& min);

	//////////////////////////




	/////////////////////////////////////////////////////////////
	//       методы для взаимодействия с пользователем         //
	/////////////////////////////////////////////////////////////

	/* 1 - добавление */
	static bool Add();
	/* 2 - удаление */
	static bool Delete();
	/* 3 - редактирование */
	static bool Edit();
	/* 4 - печать */
	static bool Print();
	/* 5 - поиск */
	static bool Search();
	/* 6 - сортировка */
	static bool Sort();
	/* 7 - поменять два элемента местами */
	static bool Swap();
	/* 8 - сохранение текущих данных */
	static bool Save();
	/* 9 - открытие таблицы */
	static bool Open();
	/* 10 - информация о разработчике */
	static void Info();

	/////////////////////////////////////////////////////////////



public:



    //////////////////////////////////////////////
    //       конструкторы и деструкторы         //
    //////////////////////////////////////////////
	
	/* получающий индекс */
	List(int & ind) {
		count++;
		index = ind;		
	};

	/* для работы с внешними массивами, например из файла */
	List( T num0,  int ind){ 
		num = num0; 
		index = ind;
	};

	/* по умолчанию */
	List() : List<T>{ List<T>::count } {};

	/* деструктор */
	~List() { count--; }

	//////////////////////////////////////////////



	
	///////////////////////////////////////////
	//       метод работы со списком         //
	///////////////////////////////////////////

	static void use();

	///////////////////////////////////////////



};