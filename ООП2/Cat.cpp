#include "Cat.h"

Cat::Cat(string name, int age, int weight) 
{
	

	setSound("��������");
	setType("�����");
	Name = name;
	setAge(age);
	setWeight(weight);
	//cout << "��������� �����" << endl;
}
// ���������� ���������� ��� ����������� �������
Cat::~Cat()
{
//	cout << "������� �����" << endl;
}

void Cat::Sound()
{
	cout << Name << " ������ " << getSound() << " �  �����" << "!!!" << endl;
}