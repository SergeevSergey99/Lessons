#include "Dog.h"
// ����������� ������� ������ Dog
void Dog::Sound() 
{
	cout << Name << " ������� ������!!!" << endl;
}
void Dog::info()
{
	cout << Name << " - ������, ������� " << Age << " ���"<< endl;
	cout << Name << " - ������, ������� ����� " << Weight << " ��" << endl;
}
// ������� - ������������� �������� ���������� ������� ������ ������ ������ ���
void Dog::setAge(int age)
{
	if (age > 0 and age < 30)
		Age = age;
}
void Dog::setWeight(int w)
{
	if (w > 0 and w < 30)
		Weight = w;
}
// ������������ - ���������� ��� ��������
// ���������� ������ ���� �� ��� � ��������� ������������ ���������� ��� ��������
Dog::Dog()
{
	cout << "��������� ������" << endl;
}
Dog::Dog(string name)
{
	Name = name;
	cout << "��������� ������" << endl;
}
Dog::Dog(string name, int age, int weight)
{
	Name = name;
	setAge(age);
	setWeight(weight);
	cout << "��������� ������" << endl;
}
// ���������� ���������� ��� ����������� �������
Dog::~Dog() 
{
	cout << "������� ������" << endl;
}