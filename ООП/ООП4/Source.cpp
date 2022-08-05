#include<iostream>
using namespace std;

class MyClass 
{
public:
	// Переопределение оператора сложения
	void operator + (int a)
	{
		cout << "Первый оператор типа MyClass, второй типа int" << endl;
	}
	// Переопределение оператора сложения с возыращением значения
	double operator + (double a)
	{
		cout << "Первый оператор типа MyClass, второй типа double" << endl;
		return a;
	}
	// Переопределение оператора инкремента
	void operator ! ()
	{
		cout << "Первый оператор типа MyClass, второго нету" << endl;
	}

};

// Перегрузка оператора вне класса
void operator - (int a, MyClass b)
{
	cout << "Первый оператор типа int, второй типа MyClass" << endl;
}

int main() 
{
	setlocale(LC_ALL, "Rus");

	MyClass m;
	
	m + 5;
	m + 3.1415; // результатом этой операции будет 3,1415. У остальных операций нет результата
	!m;
	7 - m;
}

