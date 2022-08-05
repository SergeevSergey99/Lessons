// Подключение класса
#include"Dog.h"
#include"Cat.h"
#include"Duck.h"

class base 
{
public:
	base() 
	{
		cout << "Вызов базового конструктора" << endl;
	}
	virtual void func() = 0;
};

class A : virtual public base
{
public:
	A()
	{
		cout << "Вызов A конструктора" << endl;
	}
	void func() { cout << "A" << endl; }
};
class B : virtual public base
{
public:
	B()
	{
		cout << "Вызов B конструктора" << endl;
	}
	void func() { cout << "B" << endl; }
};

class C : public A, public B 
{
public:
	C()
	{
		cout << "Вызов C конструктора" << endl;
	}
	void func() { cout << "C" << endl; }

};


// Сама программа
int main()
{
	setlocale(LC_ALL, "Rus");
		
	// Создаем объект класса Dog
	Dog d("Бобик", 10, 15);// вызов конструктора
	Cat c("Барсик", 4, 6);// вызов конструктора
	Duck duck("Дональд", 2, 3);// вызов конструктора
	/*
 // Собака
//	d.info();
	d.Sound();
// Кошка
//	c.info();
	c.Sound();
// Утка
//	duck.info();
	duck.Sound();*/
	Animal * zoo[] = { &d, &c, &duck };
	
	for (int i = 0; i < size(zoo); i++)
	{
		cout << "Вы проходите мимо загона номер " << i + 1 << endl;
		cout << "Вы видите " << zoo[i]->getType() << " с именем "<< zoo[i]->Name << endl;
		zoo[i]->Sound();
		cout << "Вы идете дальше" << endl;
	}
	
	// вызов деструктора
}