#include<iostream>
#include <windows.h>
using namespace std;

class Device 
{
public:
	void PowerOn() 
	{
		cout << "��������� ����������" << endl;
	}
};

class Phone : public virtual Device {/***/};
class Computer : public virtual Device {/***/};

// ����� ��������� ����������� ���������� ����� �������
class SmartPhone : public Phone, public Computer
{};

int main() 
{
	Phone p;
	p.PowerOn(); // �������� �������
	Computer cp;
	cp.PowerOn(); // �������� ���������
	SmartPhone sp;
	sp.PowerOn(); // �������� ��������
}