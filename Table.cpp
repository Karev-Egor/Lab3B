#include "Table.h"
#include <iostream>
#include <string.h>
#include <stdexcept>
using namespace std;

namespace Hi {
	Table::Table() : top(0)
	{}



	Table::Table(const Item& Elem)
	{
		int key;
		char info[100];
		top = 0;
		mas[top] = Elem;
	}

	Table& Table:: operator +=(Table & tab) 
	{
		int k = 0;
		this->addElem(mas[top].m_key, mas[top].m_info);
		return *this;
	}



	std::istream& operator >> (std::istream& s, Table& tab)
	{
		int n = 0, top;
		int key;
		char info[100];
		top = n;

		for (int i = 0; i < n; i++)
		{
			cout << "insert key and info";
			key = getNum("Enter key -> ");
			s >> info;
			tab.mas[i] = Item(key, info);
			return s;
		}
	}


	void getstr(const char* msg, char* str)
	{
		//char* str = new char[255];
		char* tmp = new char[255];
		int num;

		cout << msg;
		cin >> str;
		while (cin.peek() != '\n')
		{
			cin >> tmp;
			num = strlen(str);
			str[num] = ' ';
			for (int k = 0; k < strlen(tmp); k++)
				str[num + k + 1] = tmp[k];
			str[num + strlen(tmp) + 1] = '\0';
		};
		cin.ignore(255, '\n');	// очистим входной поток до Enter-а
	}


	int getNum(const char* msg)
	{
		int k;
		const char* errmsg = "";
		do
		{
			std::cout << errmsg << std::endl;
			std::cout << msg;
			std::cin >> k;
			if (!(std::cin.good()) || k < 0)
			{
				errmsg = "Invalid value, try again\n";
				std::cin.clear();
				std::cin.ignore(255, '\n');
			}
			else
			{
				std::cin.clear();
				return k;
			}

		} while (true);
	}


	


	std::ostream& operator << (std::ostream& s, const Table& tab)
	{
		Table tmp = tab;
		Item* IT = tmp.getitem();
		for (int i = 0; i < tab.topo(); ++i)
		{
			if (IT[i].m_busy == 1)
				s << "Key-> " << IT[i].m_key << " Info-> " << IT[i].m_info << std::endl;
			else if (IT[i].m_busy == 2)
				s << "Key-> " << IT[i].m_key << " Info-> " << IT[i].m_info << " DELETED" << std::endl;
		}
		return s;
	}

	char* Table::operator [](int key)
	{
		for (int i = 0; i < top; ++i)
		{
			if (key == mas[i].m_key && mas[i].m_busy == 1)
			{
				return mas[i].m_info;
			}
		}
		return NULL;
	}



	bool  Table::operator()(int key) const
	{
		for (int i = 0; i < top; ++i)
		{
			if (key == mas[i].m_key && mas[i].m_busy == 1)
				return true;
		}
		return false;

	}

	Table& Table::operator-=(int k)
	{
		this->delElem(k);
		return *this;
	}


	int Table::findindex(int k)
	{
		for (int i = 0; i < top; ++i)
		{
			if (k == mas[i].m_key && mas[i].m_busy == 1)
			{
				return i;
			}
		};
		return -1;
	}

	
	void Table::clear()
	{
		for (int i = 0; i < top; ++i)
		{
			if (mas[i].m_busy == 2)
			{
				for (int j = i; j < (top - 1); ++j)
				{
					mas[j].m_busy = mas[j + 1].m_busy;
					strcpy_s(mas[j].m_info, mas[j + 1].m_info);
					//for (int g = 0; g < 10; ++g)
						//mas[j].m_info[g] = mas[j + 1].m_info[g];
					mas[j].m_key = mas[j + 1].m_key;
				}
				mas[top - 1].m_busy = 0;
				mas[top - 1].m_key = -1;
				strcpy_s(mas[top - 1].m_info, "");
				--top;
				--i;
			}
		}
	}


	void Table::SetN(int n)
	{
		int key;
		char info[100];

		if (n < 1 || n > 10)
			throw std::length_error("");


		for (int i = 0; i < n; i++)
		{
			cout << "insert key and info";
			key = getNum("Enter key -> ");
			getstr("Enter info -> ", info);
			mas[i].m_key = key;
			strcpy_s(mas[i].m_info, info);
			mas[i].m_busy = 1;
		}
		top = n;
	}

	int Table::SetTop(int n)
	{
		top = n;
		return n;
	}

	int Table::addElem(int key, char* info)
	{
		if (top == SZ)
		{
			std::cout << "Table overflow!" << endl;
			return 0;
		}
		for (int i = 0; i < SZ; ++i)
		{
			if (key == mas[i].m_key)
			{
				cout << "Key  not unique" << endl;
				return -1;
			}

			if (mas[i].m_busy == 0 && key != mas[i].m_key)
			{
				mas[i].m_busy = 1;
				strcpy_s(mas[i].m_info, info);
				mas[i].m_key = key;
				top++;
				return 0;
			}
		}
		return -1;
	}

	void Table::delElem(int key)
	{
		int ind;
		ind = findindex(key);
		if (ind != -1)
		{
			mas[ind].m_busy = 2; // 2 - элемент удален
		}
		else
			cout << "Key not found\n";
	}
}