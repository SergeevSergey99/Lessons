#include "Dog.h"
// ����������� ������� ������ Dog

// ������������ - ���������� ��� ��������
// ���������� ������ ���� �� ��� � ��������� ������������ ���������� ��� ��������

Dog::Dog(string name, int age, int weight)
{
	setSound("���");
	setType("������");
	Name = name;
	setAge(age);
	setWeight(weight);
	//cout << "��������� ������" << endl;
}
// ���������� ���������� ��� ����������� �������
Dog::~Dog() 
{
	//cout << "������� ������" << endl;
}

void Dog::Sound()
{
	cout << Name << " ������ " << getSound() << " �  �����" << "!!!" << endl;
}