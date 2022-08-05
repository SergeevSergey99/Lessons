#include<iostream>
using namespace std;

// Объявление класса B чтобы его можно было использовать в классе A
class B;

class A 
{
private:
	int x;
public:
	// Конструктор
	A(int a) { x = a; }
	// дружественная функция
	// Функция видит только то что написано выше, поэтому 
	// в 5 строчке нужно было объявить B чтобы функция знала что такой класс будет
	friend int sum(A a, B b);
};

class B 
{
private:
	int y;
public:
	// Конструктор
	B(int b) { y = b; }
	// дружественная функция
	friend int sum(A a, B b);
};

// Определение дружественной функции
int sum(A a, B b) 
{
	// Функция имеет доступ к private элементам классов
	int result = a.x + b.y;
	return result;
}

int main() 
{
	A a(5);
	B b(7);
	cout << sum(a, b) << endl;
}

