#include "Duck.h"

Duck::Duck(string name, int age, int weight)
{
	setSound("Крякание");
	setType("Утка");
	Name = name;
	setAge(age);
	setWeight(weight);
	cout << "Появилась Утка" << endl;
}

Duck::~Duck()
{
	cout << "Исчезла Утка" << endl;

}
