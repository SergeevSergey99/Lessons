#pragma once
#include<iostream>
#include<string>
using namespace std;
// Сам класс
class Dog
{
private:
	int Age;
	int Weight;
public:
	string Name;

	Dog();
	Dog(string name);
	Dog(string name, int age, int weight);
	~Dog();
	
	void Sound();
	void setAge(int age);
	void setWeight(int w);
	void info();
};
