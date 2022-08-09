#include<iostream>
#include <windows.h>
using namespace std;

class Phone 
{
public:
	void Call(long long number)
	{
		cout << "Происходят вызов абонента " << number << endl;
	}
};

class Computer
{
public:
	void Calc(int time) 
	{
		cout << "Происходят какие то вычисления" << endl;
		Sleep(time); // Тут будет задержка на указанное количество мс
		cout << "Вычисления закончены!" << endl;

	}
};

// класс Смартфона унаследовал функционал обоих классов
class SmartPhone : public Phone, public Computer
{};

int main() 
{
	setlocale(LC_ALL, "Rus");

	SmartPhone sp;
	sp.Calc(2000);
	sp.Call(79999999999);
}

