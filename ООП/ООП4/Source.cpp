#include<iostream>
using namespace std;

class MyClass 
{
public:
	// ��������������� ��������� ��������
	void operator + (int a)
	{
		cout << "������ �������� ���� MyClass, ������ ���� int" << endl;
	}
	// ��������������� ��������� �������� � ������������ ��������
	double operator + (double a)
	{
		cout << "������ �������� ���� MyClass, ������ ���� double" << endl;
		return a;
	}
	// ��������������� ��������� ����������
	void operator ! ()
	{
		cout << "������ �������� ���� MyClass, ������� ����" << endl;
	}

};

// ���������� ��������� ��� ������
void operator - (int a, MyClass b)
{
	cout << "������ �������� ���� int, ������ ���� MyClass" << endl;
}

int main() 
{
	setlocale(LC_ALL, "Rus");

	MyClass m;
	
	m + 5;
	m + 3.1415; // ����������� ���� �������� ����� 3,1415. � ��������� �������� ��� ����������
	!m;
	7 - m;
}

