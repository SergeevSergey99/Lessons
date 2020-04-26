#include "Animal.h"
void Animal::Sound()
{
	cout << Name << " издает "<< sound <<"!!!" << endl;
}
void Animal::info()
{
	cout << Name << " - "<< type <<", в возрасте " << Age << " лет" << endl;
	cout << Name << " - " << type << ", весом " << Weight << " кг" << endl;
}
// сеттеры - устанавливают значения переменных которые нельзя менять просто так
void Animal::setAge(int age)
{
	if (age > 0 and age < 30)
		Age = age;
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
void Animal::setType(string s)
{
	type = s;
}


Animal::Animal()
{
	cout << "Появилось животное" << endl;
}
Animal::~Animal()
{
	cout << "Исчезло животное" << endl;
}