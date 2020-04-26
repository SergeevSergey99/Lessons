// Подключение класса
#include"Dog.h"
#include"Cat.h"

// Сама программа
int main()
{
	setlocale(LC_ALL, "Rus");

	// Создаем объект класса Dog
	Dog d("Бобик", 10, 15);// вызов конструктора
	
	d.info();
	d.Sound();

	Cat c("Барсик", 4, 6);// вызов конструктора

	c.info();
	c.Sound();
	

	// вызов деструктора
}