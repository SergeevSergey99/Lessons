#include "Cat.h"

Cat::Cat(string name, int age, int weight) 
{
	

	setSound("Мяуканье");
	setType("Кошка");
	Name = name;
	setAge(age);
	setWeight(weight);
	//cout << "Появилась кошка" << endl;
}
// деструктор вызывается при уничтожении объекта
Cat::~Cat()
{
//	cout << "Исчезла кошка" << endl;
}

void Cat::Sound()
{
	cout << Name << " издает " << getSound() << " и  шипит" << "!!!" << endl;
}