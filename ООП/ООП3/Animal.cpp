#include "Animal.h"
/*void Animal::Sound()
{
	cout << Name << " ������ "<< sound <<"!!!" << endl;
}*/
void Animal::info()
{
	cout << Name << " - "<< type <<", � �������� " << Age << " ���" << endl;
	cout << Name << " - " << type << ", ����� " << Weight << " ��" << endl;
}
// ������� - ������������� �������� ���������� ������� ������ ������ ������ ���
void Animal::setAge(int age)
{
	if (age > 0 and age < 30)
		Age = age;
}
string Animal::getType()
{
	return type;
}
void Animal::setWeight(int w)
{
	if (w > 0 and w < 30)
		Weight = w;
}
void Animal::setSound(string s)
{
	sound = s;
}
string Animal::getSound()
{
	return sound;
}
void Animal::setType(string s)
{
	type = s;
}


Animal::Animal()
{
	//cout << "��������� ��������" << endl;
}
Animal::~Animal()
{
	//cout << "������� ��������" << endl;
}