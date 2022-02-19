#include "List.h"

template<class T>
int List<T>::count = 0;
// начало списка
template<class T>
List<T>* List<T>::head = nullptr;
// конец списка
template<class T>
List<T>* List<T>::tail = nullptr;
// буферный указатель
template<class T>
List<T>* List<T>::buf = nullptr;

template<class T>
string List<T>::Fpath = "data.txt";

template <class T>
void List<T>::consoleSh()
{
	cout << " _________________";
	cout << "\n/ # |    Число    \\";
	cout << "\n -----------------";
}


template <class T>
ofstream & List<T>::fileSh(ofstream & out)
{
	// TODO: вставьте здесь оператор return
	out << " _________________";
	out << "\n/ # |    Число    \\";
	out << "\n -----------------";
	return out;
}


template<class T>
inline bool List<T>::saved()
{
	if (empty())return true;
	try
	{
		ifstream in;
		in.open(Fpath);
		if (!in.is_open())throw exception{};
		for (int i = 0; i < 3; i++) {
			string buf0;
			getline(in, buf0);
		}
		int count = 0;


		buf = head;
		while (!(in.eof())) {
			count++;
			List<T>* buffer1 = buf;
			if (buf == nullptr)return false;
			
			List<T>* b = new List{ T{}, count};
		    in >> b;
			
			if ((buffer1 ->operator!= (b))) return false;
			delete b;
			b = nullptr;
			buffer1 = buffer1->next;
 			buf = buffer1;

		}
		in.close();	
	}
	catch (const std::exception&)
	{
		cout << "Ошибка oткрытия таблицы!\nНевозможно сравнить содержимое!" << endl;
		return false;
	}
	return true;
}


template<class T>
inline void List<T>::print(const bool & all_l, const bool & strght)
{
	string req1 = "Введите с какого элемента начать вывод: ",
		req2 = "Введите до какого элемента выводить: ";
	int strt = 1, end = count;

	if (!all_l) {
		cout << req1;
		Enter_check(strt, count, 1);
		cout << req2;
		Enter_check(end, count, strt);
	}
	consoleSh();
	
	List <T>* ending = nullptr;
	
	if (all_l) {
		if (strght) {
			ending = tail;
			buf = head;
		}
		else {
			ending = head;
			buf = tail;
		}			
	}
	else {
		if (strght){
			buf->operator[](end);
			ending = buf;
			buf->operator[](strt);
		}
		else {
			buf->operator[](strt);
			ending = buf;
			buf->operator[](end);
		}
			
	}
	int cur_counter = 0;
    while (buf!= (strght ? ending->next : ending->prev)) {
		cur_counter++;
		*buf << cout;
		buf = strght ? buf->next : buf->prev;
	}
	cout<< endl << "Количество экземпляров: " << count << endl;
	cout << "Выведено экземпляров: " << cur_counter << endl;

}

template<class V>
ifstream& operator>>(ifstream& in, List<V>* a)
{
	// TODO: вставьте здесь оператор return
	string buf1;
	getline(in, buf1);
	int size = 2;
	vector<string> buf0(size);
	int length = 1;
	int counter = 0;
	while (length < buf1.length()) {
		if (buf1[length] != ' ' && (buf1[length] != '|' && length != 1))
			buf0[counter] += buf1[length];
		else if (buf1[length] == '|' && length != 1)
			counter++;
		length++;
	}
	try
	{
		// если дробное
		a->num = stod(buf0[1]);
	}
	catch (const std::exception&)
	{
		// в других случаях
		a->num = stoll(buf0[1]);
	}
	getline(in, buf1);
	return in;
}



template<class T>
inline bool List<T>::Add()
{

	string middle = "2 - В середину ";
	middle += count > 2 ? ("от 1 до " + to_string(count - 1)) : "(недоступно!)";
	vector<string>
		str1
	{
	"Выберите куда вставить: ",
	"1 - В начало",
	middle,
	"3 - В конец"
	},
		str2
	{
	"Выберите количество элементов: ",
	"1 - По умолчанию",
	"2 - Ввести вручную"
	}, 
		str3
	{
	"Выберите способ заполнения: ",
	"1 - Автоматически из файла",
	"2 - Вручную"
	};
	vector<int> fil1(str1.size()), fil2(str2.size()), fil3(str3.size());
	fil1[0] = 25;
	fil2[0] = 25;
	fil3[0] = 25;
	for (int i = 1; i < fil1.size(); i++)
		fil1[i] = 15;
	for (int i = 1; i < fil2.size(); i++)
		fil2[i] = 15;
	for (int i = 1; i < fil3.size(); i++)
		fil3[i] = 15;
	MENU m1(str1, fil1), m2(str2, fil2), m3(str3, fil3);

	int pos = 0, kol = 0, meth = 0;
	while (true) {
		pos = m1.show();
		if (pos == 1 || (count > 2? pos == 2: false) || pos == 3)  break;
		if(pos == 0) return true;
	}
	while (true) {
		kol = m2.show();
		if (kol == 1|| kol == 2) break; 
		if (kol== 0) return true;
	}
	while (true) {
		meth = m3.show();
		if (meth == 1 || meth == 2) break;
		if (meth == 0) return false;
	}
	try
	{
		// 	static void add(const int& pos, const int &kol, const int & meth);
		add(pos, kol, meth);
	}
	catch (const std::exception&)
	{
		cout << "Ошибка вставки!!" << endl;
		return false;
	}
	return true;
}

template<class T>
inline bool List<T>::Delete()
{
	if (empty())return true;
	string middle = "2 - Из середины ";
	middle += count > 2 ? ("от 1 до " + to_string(count - 1)) : "(недоступно!)";
	vector<string>
		str1
	{
	"Выберите откуда удалить: ",
	"1 - Из начала",
	middle,
	"3 - Из конца"
	},
		str2
	{
	"Выберите количество удаляемых элементов: ",
	"1 - По умолчанию",
	"2 - Ввести вручную"
	};
	vector<int> fil1(str1.size()), fil2(str2.size());
	fil1[0] = 25;
	fil2[0] = 25;

	for (int i = 1; i < fil1.size(); i++)
		fil1[i] = 15;
	for (int i = 1; i < fil2.size(); i++)
		fil2[i] = 15;

	MENU m1(str1, fil1), m2(str2, fil2);

	int pos = 0, kol = 0;
	while (true) {
		pos = m1.show();
		if (pos == 1 || (count > 2 ? pos == 2 : false) || pos == 3)  break;
		if (pos == 0) return true;
	}
	while (true) {
		kol = m2.show();
		if (kol == 1) { clear(); return true; }
		if (kol == 2) break;
		if (kol == 0) return true;
	}

	try
	{
		// 	static void add(const int& pos, const int &kol, const int & meth);
		del(pos, kol);
	}
	catch (const std::exception&)
	{
		cout << "Ошибка удаления!!" << endl;
		return false;
	}
	return true;

}

template<class T>
inline bool List<T>::Edit()
{
	if (empty())return true;
	int pos1 = 1;
	string req1 = "Введите позицию редактируемой строки: ";
	try
	{
		cout << req1; Enter_check(pos1, count, 1);
		buf = buf->operator[](pos1);
		buf->operator<<(cout) << endl;
		 
		buf->operator>> (cin);
		buf->operator<<(cout) << endl;

	}
	catch (const std::exception&)
	{
		cout << "Проблема с редактированием!" << endl;
		return false;
	}
	return true;
}


template<class T>
inline bool List<T>::Print()
{
	if (empty())return true;
	vector<string>
		str1
	{
	"Выберите вид печати:",
	"1 - Вывести весь список",
	"2 - Вывести часть списка"
	},
		str2
	{
	"Выберите порядок вывода:",
	"1 - Прямой",
	"2 - Обратный"
	};
	vector<int> fil(str1.size());
	fil[0] = 25;
	for (int i = 1; i < fil.size(); i++) {
		fil[i] = 15;
	}
	MENU m1(str1, fil), m2(str2, fil);
	bool all_l = false, strght = false;
	int m = 0;
	while (true) {
		m = m1.show();
		if (m == 1) { all_l = true; break; }
		else if (m == 2) { break; }
		else if (m == 0) { return true; }
	}
	while (true) {
		m = m2.show();
		if (m == 1) { strght = true; break; }
		else if (m == 2) { break; }
		else if (m == 0) { return true; }
	}	
	try
	{
		print(all_l, strght);
	}
	catch (const std::exception&)
	{
		cout << "Ошибка печати!!" << endl;
		return false;
	}
	return true;
}

template<class T>
inline bool List<T>::Search()
{
	if (empty())return true;
	vector<string>
		str1
	{
	"Выберите вид поиска:",
	"1 - Больше введенного значения",
	"2 - Меньше введенного значения"
	};
	string var = "Введите значение для поиска: ";
	T search_val = 0;
	bool bigger = false;
	int counter = 0;
	vector<int> fil(str1.size());
	fil[0] = 25;
	for (int i = 1; i < fil.size(); i++) {
		fil[i] = 15;
	}
	MENU m1(str1, fil);
	while (true) {
	    int m = m1.show();
		if (m == 1) { bigger= true; break; }
		else if (m == 2) { break; }
		else if (m == 0) { return true; }
	}
	cout << var; Enter_check(search_val, 1000, -1000);
	buf = head;
	consoleSh();
	while (buf != nullptr) {
		if (bigger ? search_val <= buf->num: search_val >= buf->num) {
			buf->operator<<(cout);
			counter++;
		}
		buf = buf->next;
	}
	cout << endl << "Количество найденных: " << counter << endl;
	cout << "Количество экземпляров: " << count << endl;
	return false;
}


template<class T>
inline bool List<T>::Sort()
{
	print(true, true);// вывод всего списка в прямом порядке
	if (empty())return true;
	vector<string> str{
	"Выберите порядок сортировки: ",
	"1 - По возрастанию",
	"2 - По убыванию"};

	vector<int> fil(str.size());
	fil[0] = 25;
	for (int i = 1; i < fil.size(); i++)
		fil[i] = 15;
	MENU m(str, fil);

	for (;;) {
		int b = m.show();
		try
		{
			switch (b) {
			case 0: return true;
			case 1:
				sort();// по возрастанию
				return true;
			case 2:
				sort(false);// по убыванию
				return true;
			}
		
		}
		catch (const std::exception&)
		{
			return false;
		}
	}
	print(true, true);// вывод всего списка в прямом порядке
	return true;
}

template<class T>
inline bool List<T>::Swap()
{
	string var1 = "Введите номер 1-го элемента: ",
		var2 = "Введите номер 2-го элемента: ";
	int num1 = 0, num2 = 0;
	cout << var1; Enter_check(num1, count, 1);
	cout << var2; Enter_check(num2, count, 1);
	try
	{
		print(true, true);
		List<T>* buf1 = buf->operator[](num1), * buf2 = buf->operator[](num2);
		swapPointers(buf1, buf2);
		print(true, true);
	}
	catch (const std::exception&)
	{
		cout << "Ошибка свапа!!" << endl;
		return false;
	}
	return true;
	
}



template<class T>
inline bool List<T>::Save()
{
	if (empty())return true;

	vector<string>
		str1
	{
	"Выберите путь:",
	"1 - По умолчанию",
	"2 - Текущий",
	"3 - Ввести вручную"
	};

	T search_val = 0;
	bool bigger = false;
	int counter = 0;
	vector<int> fil(str1.size());
	fil[0] = 25;
	for (int i = 1; i < fil.size(); i++) {
		fil[i] = 15;
	}
	MENU m1(str1, fil);
	while (true) {
		int m = m1.show();
		if (m == 1) { setPath("data.txt"); break; }
		else if (m == 2) { break; }
		else if (m == 3) { setPath(); break; }
		else if (m == 0) { return true; }
	}
	try
	{
		ofstream out;
		out.open(Fpath);
		fileSh(out);
		buf = head;
		while (buf != nullptr) {
			buf->operator<< (out);
			buf = buf->next;
		}
		out.close();
	}
	catch (const std::exception&)
	{
		cout << "Ошибка сохранения таблицы!" << endl;
		return false;
	}
	cout << "Данные сохранены в: " << Fpath << endl;
	return true;
}


template<class T>
inline bool List<T>::Open()

{
	vector<string>
		str1
	{
	"Выберите путь:",
	"1 - По умолчанию",
	"2 - Текущий",
	"3 - Ввести вручную"
	};
	T search_val = 0;
	bool bigger = false;
	int counter = 0;
	vector<int> fil(str1.size());
	fil[0] = 25;
	for (int i = 1; i < fil.size(); i++) {
		fil[i] = 15;
	}
	MENU m1(str1, fil);
	while (true) {
		int m = m1.show();
		if (m == 1) { setPath("data.txt"); break; }
		else if (m == 2) { break; }
		else if (m == 3) { setPath(); break; }
		else if (m == 0) { return true; }
	}

	try
	{
		ifstream in;
		clear();
		in.open(Fpath);
		if (!in.is_open())throw exception{};
		for (int i = 0; i < 3; i++) {
			string buf0;
			getline(in, buf0);
		}
		buf = head;
		while (!(in.eof())) {
			buf = buf->add(head, tail);
			in >> buf;
		}
		in.close();
	}
	catch (const std::exception&)
	{
		cout << "Ошибка oткрытия таблицы!" << endl;
		Save();
		return false;
	}
	cout << "Данные считано из: " << Fpath << endl;
	return true;
}


template<class T>
inline void List<T>::Info()
{
	cout << "Фамилия: Вариводин\nИмя: Максим\nГруппа: КН-320Б\n" <<
		"Рабочая почта: maksym.varivodin@gmail.com\n"<<
		"Специальность: 122 - Компьютерные науки\n";
	system("pause");

}

//template<>
//class List<string> {
//	void ConsoleSh() {
//		cout << " _________________\n";
//		cout << "/ # |   Cтрока    \\\n";
//		cout << " -----------------\n";
//	}
//	ofstream& FileSh(ofstream & out) {
//		// TODO: вставьте здесь оператор return
//		out << " _________________\n";
//		out << "/ # |   Cтрока    \\\n";
//		out << " -----------------\n";
//		return out;
//	}
//};

//template<>
//class List<char> {
//	void ConsoleSh() {
//		cout << " _________________\n";
//		cout << "/ # |   Символ    \\\n";
//		cout << " -----------------\n";
//	}
//	ofstream& FileSh(ofstream & out) {
//		// TODO: вставьте здесь оператор return
//		out << " _________________\n";
//		out << "/ # |   Символ    \\\n";
//		out << " -----------------\n";
//		return out;
//	}
//};

template<class T>
void List<T>::swap(List<T>* a, List<T>* b)
{
	T buf = a->num;
	a->num = b->num;
	b->num = buf;
}

template<class T>
inline void List<T>::swapPointers(List<T>*& a, List<T>*& b)
{
	// общий случай
	List<T>* prev = b->prev, *next = b->next;
	
	b->prev = a->prev;
	a->prev = prev;
	b->next = a->next;
	a->next = next;
	if (b->prev != nullptr)
		b->prev->next = b;
	else head = b;
	if (b->next != nullptr)
		b->next->prev = b;
	else tail = b;
	if (a->prev != nullptr)
		a->prev->next = a;
	else head = a;
	if (a->next != nullptr)
		a->next->prev = a;
	else tail = a;

}


template<class T>
void List<T>::use()
{
	BigColor Color;
	vector<string> str{
	   "МЕНЮ",
	   "1 - Добавление",
	   "2 - Удаление",
	   "3 - Эдит",
	   "4 - Печать",
	   "5 - Поиск",
	   "6 - Сортировка",
	   "7 - Взаимозамена",
	   "8 - Сохранение таблицы",
	   "9 - Открытие таблицы",
	   "10 - О разработчике",
	   "11 - Выход"
	}, 
		str1{
   "Текущие данные не сохранены! Хотите сохранить?",
   "1 - Да",
   "2 - Нет"
	};

	vector<int> fil(str.size()), fil1(str1.size());
	fil[0] = 20;
	fil1[0] = 5;
	for (int i = 1; i < fil.size(); i++) {
		fil[i] = 10;		
	}		
	for (int i = 1; i < fil1.size(); i++) {
		fil1[i] = 10;
	}
	MENU m(str, fil, Color.Black, Color.White), 
		m1(str1, fil1, Color.Black, Color.White);

	for (;;) {
		
		system("cls");
		int b = m.show();
		switch (b) {
		case 1:	Add();   break;
		case 2:	Delete();break;
		case 3:	Edit();	 break;
		case 4:	Print(); break;
		case 5: Search();break;
		case 6:	Sort();  break;
		case 7: Swap(); break;
		case 8: Save();	 break;
		case 9: Open();  break;
		case 10: Info();  break;
		}
		indxCheck();	
		if (b == 11 || b == 0)break;
		system("pause");
		system("mode con cols=78 lines=50");//задание размеров окна консоли
	
	}
	if(!saved())
	for (;;) {
		int b = m1.show();
		switch (b) {
		case 0: return;
		case 1:	Save(); clear();	return;
		case 2:	clear(); return;
		}
	}
}


template<class T>
inline void List<T>::indxCheck()
{
	int ind = 0;
	buf = head;
	while (buf != nullptr) {
		ind++;
		buf->index = buf->index == ind ? buf->index : ind;
		buf = buf->next;
	}
}




template<class T>
void List<T>::operator()(const T & a) { num = a; }


template <class T>
List<T>*& List<T>::operator[] 
(const int & ind)
{

	if (ind < 1)
		return head;
	else if (ind > count)
		return tail;
	buf = head;
	while (buf->index != ind && buf->next != nullptr)buf = buf->next;
	return buf;
}


template <class T>
List<T>& List<T>::operator=(const List & other)
{
	// TODO: вставьте здесь оператор return
	this->operator()(other.num);
	return *(this);
}




template<class T>
inline void List<T>::randomFromFile()
{
	ifstream CIN;
	ofstream COUT;
	string path1 = "numbs.txt";
	COUT.open(path1, ios::app);
	COUT.close();
	CIN.open(path1, ios::app | ios::in);
	if (!CIN.is_open()) { cout << "Error!"; }
	else {
		vector<T> a(0);
		while (!CIN.eof()) {
			string s;
			getline(CIN, s);
			vector<string> buf(0);
			int iter = 0, i = 0;
			while (iter != s.length())
			{
				if (s[iter] == ' ') { iter++; i++; }
				else if (s[iter] != ' ') {
					if (iter > 0) {
						if (s[iter - 1] == ' ' || buf.size() == 0)
							buf.resize(buf.size() + 1);
					}
					else
						buf.resize(buf.size() + 1);
					

					buf[i] += s[iter];
					iter++;
				}
			}
			a.resize(a.size() + buf.size());
			int k = a.size() - buf.size(), j = 0;
			for (; j < buf.size(); ) {
				try
				{
					// если дробное
					a[k] = stod(buf[j]);
				}
				catch (const std::exception&)
				{
					// в других случаях
					a[k] = stoll(buf[j]);
				}
				k++; j++;
			}
		}
		try
		{
			string err = "Заполните файл числами!";
			if (a.size() <= 0)throw err;
			int b = rand() % a.size();
			this->num = a[b];
		}
		catch (const string&err)
		{
			cout << err<< endl;
		}

	}
	CIN.close();
}

template <class T>
List<T>* List<T>::add(List <T>*& head0, List <T>*& tail0)
{
	buf = head0 == head ? new List : new List{ T{}, 0 }; // выделение памяти под следующий элемент 
	/* если переданная голова пуста, то присваиваем */
	if (head0 == nullptr) head0 = buf;
	/* если элемент для вставки это ноль, 
	   то значит нужно создать новый корень */
	else if (this == nullptr) {
		buf->prev = head0->prev;
		buf->next = head0;
		head0->prev = buf;
	}
	else
	{
		/* любые другие случаи */
		buf->next = this->next;
		buf->prev = this;
		this->next = buf;
		/* если этот элемент не содержит информацию
		   про следующий, то это хвост */
		if (buf->next != nullptr)
			buf->next->prev = buf;
		else tail0 = buf;
	}	
	return buf;
}


template <class T>
List<T>* List<T>::del(List <T>*& head0, List <T>*& tail0)
{
	if (this == nullptr || head0 == nullptr)return nullptr;
	if (this == head0)
	{
		head0 = this->next;
		buf = head0;
		if (head0 == nullptr)tail0 = nullptr;
	}
	else if (this == tail0)
	{
		this->prev->next = nullptr;
		tail0 = this->prev;
		buf = tail0;
	}
	else {
		if (this->next != nullptr)
		{
			this->next->prev = this->prev;
		}
		this->prev->next = this->next;
		buf = this->next;
	}
	this->~List();
	return buf;
}


template<class T>
inline istream& List<T>::operator>>(istream& in)
{
	// TODO: вставьте здесь оператор return
	cout << "Введите число: ";
	Enter_check(this->num, 1000, -1000);
	return in;
}

template<class T>
inline ostream & List<T>::operator<<(ostream & out)
{

	// TODO: вставьте здесь оператор return
	int i = 0,
		text[2]{
	    to_string(this->index).length(),
	    to_string(this->num).length()
	    },
		COL[2]{ 4, 15 },
		col[2]{};
	
	string txt[]{
	to_string(this->index),
	to_string(this->num)
	};

	for (int &var : col)
	{
		var = this->col_count(text[i], COL[i]);
		i++;
	}
	i = 0;
	out << "\n";
	for (int var : col) {
		out << "|" << setw(col[i]) << txt[i] << setw(COL[i] - col[i]);
		i++;
	}
	out << "|\n"; out << " -----------------";
	return out;
}






template <class T>
void List<T>::sort(const bool & orderAZ)
{
	List<T>* buf2 = head;
	while (buf2 -> index <= count / 2)
		// кол-ство итераций вдвое меньше количества экземпляров,\
		 так как за один проход меняется сразу два числа
	{
		List<T>* buf1 = buf2 -> operator[](count - (buf2->index - 1));//нахождение последнего в текущем диапазоне
		List<T>* buf0 = buf2;// первый в текущем диапазоне
		while (buf0->index < count - (buf2->index - 1))// пока индекс в рамках текущего диапазона поиска
		{
			if (orderAZ ? buf1->operator< (buf0) : buf1->operator>(buf0)) {
				swap(buf0, buf1);
			}
			if (orderAZ ? buf2->operator>(buf0) : buf2->operator< (buf0)) {
				swap(buf2, buf0);
			}
			buf0 = buf0->next;// переход на следующий во внутреннем цикле
		}
		buf2 = buf2->next;// переход на следующий во внешнем цикле
	}
	
}


template <class T>
int List<T>::col_count(const int & a, const int & b)
{
	// a - размер строки, в - размер колонки

	int c = a + (b - 1 - a) / 2;
	return c;
}


template<class T>
inline void List<T>::add(const int& pos, const int& kol, const int& meth)
{
	int pos1 = 1, kol1 = 20, meth1 = 0;
	string req1 = "Введите позицию после которой добавлять: ",
		req2 = "Введите количество добавляемых элементов: ";
	if (count > 0) {
		switch (pos) {
		case 2: cout << req1; Enter_check(pos1, count - 1 , 1); break;
		case 3: pos1 = count; break;
		}
		buf = ((pos!= 1) ? buf->operator[](pos1) : nullptr);
	}
	else {
		buf = nullptr;
	}
	if (kol == 2) {
		cout << req2; Enter_check(kol1, 1000,1);
	}
	
	for (int i = 0; i < kol1; i++)
	{
		buf = buf->add(head, tail);	
		// в цикле
		switch (meth) {
		case 1: buf->randomFromFile();// из файла
			break;
		case 2: *buf >> cin; // вручную
			break;
		}
	}
	

}

template<class T>
inline void List<T>::del(const int& pos, const int& kol)
{
	int pos1 = 1, kol1 = 20;
	string req1 = "Введите позицию c которой удалять(этот номер тоже удалится): ",
		req2 = "Введите количество удаляемых элементов: ";
	if (count > 0) {
		switch (pos) {
		case 2: if (count <= 2)return; cout << req1; Enter_check(pos1, count - 1, 1); break;
		case 3: pos1 = count; break;
		}
		buf = ((pos != 1) ? buf->operator[](pos1) : nullptr);
	}
	else {
		return;
	}
	if (kol == 2) {
		switch (pos) {
		case 2: cout << req2; Enter_check(kol1, count - pos1, 1); break;
		case 3: cout << req2; Enter_check(kol1, count, 1); break;
		}
		
	}
	for (int i = 0; i < kol1; i++)
	{
		buf = buf->del(head, tail);
	}
}

template<class T>
inline bool List<T>::clear()
{
	if (head == nullptr) return true;
	buf = tail;
	try
	{
		while (buf != nullptr) {
			buf = buf->del(head, tail);		
		}
	}
	catch (const std::exception&)
	{
		cout << "Ошибка очистки списка!" << endl;
		return false;
	}
	return true;
}

template<class T>
inline void List<T>::setPath(const string& path)
{
	if (path != "") {
		Fpath = path;
		return;
    }
	cout << "Введите путь: ";
	getline(cin, Fpath);
}


template <class T>
ostream & operator<<(ostream & out, List<T> & a)
{
	// TODO: вставьте здесь оператор return
	int COL[2]
	{ 4, 15 },
		text[2]
	{
	to_string(a.index).length(),
	to_string(a.num).length()
	},
		col[2]{},
		i = 0;
	string txt[]{
	to_string(a.index),
	to_string(a.num)
	};
	for (int &var : col)
	{
		var = a.col_count(text[i], COL[i]);
		i++;
	}
	i = 0;
	for (int var : col) {
		cout << "|" << setw(col[i]) << txt[i] << setw(COL[i] - col[i]);
		i++;
	}
	cout << "|\n";
	cout << " -----------------\n";
	return out;
}

