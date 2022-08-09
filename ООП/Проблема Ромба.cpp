#include<iostream>
#include <windows.h>
using namespace std;

class Device 
{
public:
	void PowerOn() 
	{
		cout << "Включение устройства" << endl;
	}
};

class Phone : public virtual Device {/***/};
class Computer : public virtual Device {/***/};

// класс Смартфона унаследовал функционал обоих классов
class SmartPhone : public Phone, public Computer
{};

int main() 
{
	Phone p;
	p.PowerOn(); // включаем телефон
	Computer cp;
	cp.PowerOn(); // включаем компьютер
	SmartPhone sp;
	sp.PowerOn(); // включаем смартфон
}