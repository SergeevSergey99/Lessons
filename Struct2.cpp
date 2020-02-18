#include<iostream>
#include<time.h>
#include<string>
using namespace std;

struct Car
{
	string name = "";
	string color = ""; // Строка в которой содержится цвет
	int countOfCYLIINDERs = 0;
	int maxSpeed = 0;
	int USKORENIE = 0;
	int price = 0;

	int x = 0;
	int Speed = 0;
};

void PrintCar(Car car) {
	cout << "Имя:\t\t" << car.name << endl;
	cout << "Цвет:\t\t" << car.color << endl;
	cout << "Цилиндры:\t" << car.countOfCYLIINDERs << endl;
	cout << "Скорость:\t" << car.maxSpeed << " км/с" << endl;
	cout << "Ускорение:\t" << car.USKORENIE << endl;
	cout << "Цена:\t\t" << car.price << " копеек" << endl << endl;
}
Car GetRandomCar() {
	Car car;
	string colors[] = {
		"синий",
		"красный",
		"зеленый",
		"золотой",
		"черный",
		"белый",
		"ржавый"
	};
	string names[] = {
			"феррари",
			"ламборгини",
			"жигуль",
			"трактор",
			"кабриолет",
			"тесла",
			"астон мартин"
	};
	car.maxSpeed = 100 + rand() % 251; // 100 - 350
	car.USKORENIE = 10 + rand() % 131; // 10 - 140
	car.price = car.maxSpeed + car.USKORENIE * 2 + rand() % 100; // 1000 - 1000000
	car.countOfCYLIINDERs = 2 * (1 + rand() % 21);// 2 - 42
	car.color = colors[rand() % 7];
	car.name = names[rand() % 7];
	return car;
}

int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	const int n = 3;

	Car raceCars[n];

	// race

	for (int i = 0; i < n; i++)
	{
		raceCars[i] = GetRandomCar();
		raceCars[i].name += "_" + to_string(i+1);
		
		PrintCar(raceCars[i]);
	}

	int lenght_of_trace = 10000;
	int c = 0;
	while (c < n) 
	{
		for (int i = 0; i < n; i++)
		{
			raceCars[i].Speed += raceCars[i].USKORENIE;
			if (raceCars[i].Speed > raceCars[i].maxSpeed)
				raceCars[i].Speed = raceCars[i].maxSpeed;

			raceCars[i].x += raceCars[i].Speed;
			if (raceCars[i].x >= lenght_of_trace)
			{
				c++;
				raceCars[i].Speed = 0;
				raceCars[i].x = 0;
				raceCars[i].USKORENIE = 0;
				cout << "Машина " << raceCars[i].name << " преодолела финишную черту" << endl;
			}
		}
	}
	return 0;
}
