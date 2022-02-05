#include<iostream>
using namespace std;

struct Car 
{
	string name;	// ���� / ������� / �������� / ��� / �����
	int maxSpeed;	// 200 - 400
	int armor;		// 40 - 250
	int fuel;		// 20 - 200
	float boost;	// 2.5 - 10

	Car() // �����������
	{
		SetRandomCar();
	}
	void SetRandomCar()
	{
		string names[] = { "����" ,"�������" ,"��������", "���", "�����" };
		name = names[rand() % 5];

		maxSpeed = 200 + rand() % 201;
		armor = 40 + rand() % 211;
		fuel = 20 + rand() % 181;
		boost = 2.5 + (rand() % 76) / 10.0;
	}
	void PrintCar()
	{
		cout << "Car name is " << name << endl;
		cout << "Car maxSpeed is " << maxSpeed << endl;
		cout << "Car armor is " << armor << endl;
		cout << "Car fuel is " << fuel << endl;
		cout << "Car boost is " << boost << endl;
	
		cout << endl;
	}
};


int main() {
	setlocale(LC_ALL, "RUS");
	srand(time(0));

	Car myCars[5];

	for (size_t i = 0; i < 5; i++)
	{
		myCars[i].PrintCar();
	}

}