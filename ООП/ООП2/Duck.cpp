#include "Duck.h"

Duck::Duck(string name, int age, int weight)
{
	setSound("��������");
	setType("����");
	Name = name;
	setAge(age);
	setWeight(weight);
	cout << "��������� ����" << endl;
}

Duck::~Duck()
{
	cout << "������� ����" << endl;

}
