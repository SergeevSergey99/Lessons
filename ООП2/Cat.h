#pragma once
#include"Animal.h"
class Cat : public Animal
{

public:
	Cat(string name, int age, int weight);
	~Cat();
	void Sound();
};

