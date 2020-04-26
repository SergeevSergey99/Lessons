#pragma once
#include<iostream>
#include<string>

using namespace std;
class Animal
{

private:
	int Age;
	int Weight;
	string sound = "какие-то звуки";
	string type = "Животное";
protected:
	void setSound(string s);
	void setType(string s);
public:
	string Name;

	void setAge(int age);
	void setWeight(int w);
	void Sound();
	void info();

	Animal();
	~Animal();
};

