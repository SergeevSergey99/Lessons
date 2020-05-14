#pragma once
#include"Animal.h"
class Duck : public Animal
{
public:
	Duck(string name, int age, int weight);
	~Duck();

	void Sound();
};

