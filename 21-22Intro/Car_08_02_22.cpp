#include<iostream>
using namespace std;

struct Car
{
	string name;
	int maxSpeed;
	float boost;
	float fuel;

	Car(string n, int m, float b, float f) 
	{
		name = n;
		maxSpeed = m;
		boost = b;
		fuel = f;
	}
	Car()
	{
		string names[] = { "Ford", "Ferrari", "BMW", "Mersedes", "Lamborgini", "Volvo"};

		name		= names[rand() % 6];			// Ford, Ferrari, BMW, Mersedes, Lamborgini, Volvo
		maxSpeed	= 200 + rand() % 201;			// 200 - 400
		boost		= 1.5 + (rand() % 86) / 10.0;	// 1.5 - 10
		fuel		= 10.3 + (rand() % 1398) / 10.0;// 10.3 - 150
	}

	void PrintCar() 
	{
		cout << "Car have name      = " << name << endl;
		cout << "Car have max speed = " << maxSpeed << endl;
		cout << "Car have boost     = " << boost << endl;
		cout << "Car have fuel      = " << fuel << endl;
		cout << endl;
	}
};


int main() 
{
	srand(time(0)); 

	Car myCar[5];

	for (size_t i = 0; i < 5; i++)
	{
		myCar[i].PrintCar();
	}
}