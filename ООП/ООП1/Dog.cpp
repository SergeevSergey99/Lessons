#include "Dog.h"
// Определение функций класса Dog
void Dog::Sound() 
{
	cout << Name << " говорит ГавГав!!!" << endl;
}
void Dog::info()
{
	cout << Name << " - собака, которой " << Age << " лет"<< endl;
	cout << Name << " - собака, которая весит " << Weight << " кг" << endl;
}
// сеттеры - устанавливают значения переменных которые нельзя менять просто так
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
// конструкторы - вызываются при создании
// Вызывается только один из них с выбранным колличеством параметров при создании
Dog::Dog()
{
	cout << "Появилась собака" << endl;
}
Dog::Dog(string name)
{
	Name = name;
	cout << "Появилась собака" << endl;
}
Dog::Dog(string name, int age, int weight)
{
	Name = name;
	setAge(age);
	setWeight(weight);
	cout << "Появилась собака" << endl;
}
// деструктор вызывается при уничтожении объекта
Dog::~Dog() 
{
	cout << "Исчезла собака" << endl;
}