#include<iostream>
using namespace std;

// Объединяем несколько переменных в структуру
struct Person
{
	string name; // строковая переменная для хранения имени 
	string lastName; // строковая переменная для хранения фамилии
	string phone; // строковая переменная для хранения телефона
	int age; // числовая переменная для хранения возраста
};

// Функция создающаяя персону с заданными значениями
Person SetStandartPerson()
{
	// Выделяем память для элемента структуры 
	Person person;
	// Чтобы изменить значения в структуре
	// указываем через точку что нужно изменить
	person.lastName = "Иванов";
	person.name = "Иван";
	person.phone = "+7(999)-999-99-99";
	person.age = 42;
	// Вместо Функции будет поставлена эта персона
	return person;
}

// Функция вывода на экран данных, хранящихся в структуре персоны
void PrintPerson(Person person)
{
	cout << endl;
	cout << "Имя: " << person.lastName << " " << person.name << endl;
	cout << "Возраст: " << person.age << endl;
	cout << "Телефон: " << person.phone << endl << endl;
}

int main()
{
	// Выделяем память для элемента структуры 
	Person person1;
	// Задаем данные у персоны вручную
	person1.name = "Петр";
	person1.lastName = "Петров";
	person1.age = 0;
	person1.phone = "+7(000)-000-00-00";
	// Печатаем person1
	PrintPerson(person1);

	// Выделяем память для элемента структуры 
	// Задаем данные у персоны по шаблону
	Person person2 = SetStandartPerson();
	// Печатаем person2
	PrintPerson(person2);
}
