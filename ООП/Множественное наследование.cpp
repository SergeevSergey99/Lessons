#include<iostream>
#include <windows.h>
using namespace std;

class Phone 
{
public:
	void Call(long long number)
	{
		cout << "���������� ����� �������� " << number << endl;
	}
};

class Computer
{
public:
	void Calc(int time) 
	{
		cout << "���������� ����� �� ����������" << endl;
		Sleep(time); // ��� ����� �������� �� ��������� ���������� ��
		cout << "���������� ���������!" << endl;

	}
};

// ����� ��������� ����������� ���������� ����� �������
class SmartPhone : public Phone, public Computer
{};

int main() 
{
	setlocale(LC_ALL, "Rus");

	SmartPhone sp;
	sp.Calc(2000);
	sp.Call(79999999999);
}

