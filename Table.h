#ifndef _Lab3_B_
#define _Lab3_B_
#include <iostream>
#include <cstring>

namespace Hi {
	int getNum(const char* msg);
	void getstr(const char* msg, char* str);

	struct Item {
		static const int L = 100; //Максимальная длина элемента
		int m_key; //Ключ
		int m_busy;//Про busy : 0 - пусто, 1 - есть элемент, 2 - элемент удален
		char m_info[L]; //Информация

		Item() : m_key(-1), m_busy(0) {}
		Item(int key, char* info) : m_key(key), m_busy(1) { strcpy_s(m_info, info); }
	};

	class Table
	{
	private:
		static const int SZ = 10; //Максимальный размер таблицы
		Item mas[SZ];
		int top;//Текущий размер таблицы
		int findindex(int k);// Поиск индекса элемента для удаления элемента
	public:
		Table();
		Table(const Item& Elem);//Заполнение
		Table& operator += (Table & tab); //Добавление элемента в таблицу // not friend //const
		bool operator () (int key) const; //Поиск элемента в таблице 
		Table& operator -= (int key); //not friend //const
		void clear();
		void SetN(int n);
		char* operator [](int key); //double const and not const
		int getSize() const { return top; } // Текущий размер таблицы
		int getMaxSize() const { return SZ; } //Максимальный размер таблицы
		friend std::ostream& operator << (std::ostream& s, const Table& tab); //Вывод таблицы
		int addElem(int key, char* info); //Добавление элемента в таблицу
		void delElem(int key);
		friend std::istream& operator >> (std::istream& s, Table& tab); //Ввод элементов
		Item* getitem() { return mas; }
		int SetTop(int n);
		int topo() const { return top; } 
	};
}
#endif