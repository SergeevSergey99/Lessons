#pragma once
#include<iostream>
#include<string>

using namespace std;
class Animal
{

private:
	int Age;
	int Weight;
	string sound = "�����-�� �����";
	string type = "��������";
protected:
	void setSound(string s);
	void setType(string s);
	string getSound();
public:
	string Name;

	string getType();
	void setAge(int age);
	void setWeight(int w);
	virtual void Sound() = 0;
	void info();

	Animal();
	~Animal();
};

