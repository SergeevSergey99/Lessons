#pragma once
#include "Animal.h"

// ��� �����
class Dog : public Animal
{
public:
	Dog(string name, int age, int weight);
	~Dog();
	void Sound();
};
