#include "Dog.h"
// Определение функций класса Dog

// конструкторы - вызываются при создании
// Вызывается только один из них с выбранным колличеством параметров при создании

Dog::Dog(string name, int age, int weight)
{
	setSound("Лай");
	setType("Собака");
	Name = name;
	setAge(age);
	setWeight(weight);
	//cout << "Появилась собака" << endl;
}
// деструктор вызывается при уничтожении объекта
Dog::~Dog() 
{
	//cout << "Исчезла собака" << endl;
}

void Dog::Sound()
{
	cout << Name << " издает " << getSound() << " и  рычит" << "!!!" << endl;
}