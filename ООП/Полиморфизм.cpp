#include<iostream>

class Base
{
public:
	// Базовый виртуальный метод
	virtual void DoSomething()
	{
		std::cout << "DoSomething Base" << std::endl;
	}
};

class A : public Base
{
public:
	// Переопределенный виртуальный метод в класса A
	virtual void DoSomething()
	{
		std::cout << "DoSomething A" << std::endl;
	}
};

class B : public Base
{
public:
	// Переопределенный виртуальный метод в класса B
	virtual void DoSomething()
	{
		std::cout << "DoSomething B" << std::endl;
	}
};

int main()
{
	Base base1, base2, base3;
	A a1, a2;
	B b1, b2;
	Base* arr[7] = { &base1, &a1, &b1, &base2, &a2, &b2, &base3 };

	for (int i = 0; i < 7; i++)
	{
		arr[i]->DoSomething();
	}
}

