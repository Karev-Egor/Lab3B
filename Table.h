#ifndef _Lab3_B_
#define _Lab3_B_
#include <iostream>
#include <cstring>

namespace Hi {
	int getNum(const char* msg);
	void getstr(const char* msg, char* str);

	struct Item {
		static const int L = 100; //������������ ����� ��������
		int m_key; //����
		int m_busy;//��� busy : 0 - �����, 1 - ���� �������, 2 - ������� ������
		char m_info[L]; //����������

		Item() : m_key(-1), m_busy(0) {}
		Item(int key, char* info) : m_key(key), m_busy(1) { strcpy_s(m_info, info); }
	};

	class Table
	{
	private:
		static const int SZ = 10; //������������ ������ �������
		Item mas[SZ];
		int top;//������� ������ �������
		int findindex(int k);// ����� ������� �������� ��� �������� ��������
	public:
		Table();
		Table(const Item& Elem);//����������
		Table& operator += (Table & tab); //���������� �������� � ������� // not friend //const
		bool operator () (int key) const; //����� �������� � ������� 
		Table& operator -= (int key); //not friend //const
		void clear();
		void SetN(int n);
		char* operator [](int key); //double const and not const
		int getSize() const { return top; } // ������� ������ �������
		int getMaxSize() const { return SZ; } //������������ ������ �������
		friend std::ostream& operator << (std::ostream& s, const Table& tab); //����� �������
		int addElem(int key, char* info); //���������� �������� � �������
		void delElem(int key);
		friend std::istream& operator >> (std::istream& s, Table& tab); //���� ���������
		Item* getitem() { return mas; }
		int SetTop(int n);
		int topo() const { return top; } 
	};
}
#endif