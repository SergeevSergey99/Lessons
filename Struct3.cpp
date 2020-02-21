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

	void PrintCar() {
		cout << "Имя:\t\t" << name << endl;
		cout << "Цвет:\t\t" << color << endl;
		cout << "Цилиндры:\t" << countOfCYLIINDERs << endl;
		cout << "Скорость:\t" << maxSpeed << " км/с" << endl;
		cout << "Ускорение:\t" << USKORENIE << endl;
		cout << "Цена:\t\t" << price << " копеек" << endl << endl;
	}

	void GetRandomCar() {
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
		maxSpeed = 100 + rand() % 251; // 100 - 350
		USKORENIE = 10 + rand() % 131; // 10 - 140
		price = maxSpeed + USKORENIE * 2 + rand() % 100; // 1000 - 1000000
		countOfCYLIINDERs = 2 * (1 + rand() % 21);// 2 - 42
		color = colors[rand() % 7];
		name = names[rand() % 7];
	}
	void Move() 
	{
		Speed += USKORENIE;
		if (Speed > maxSpeed)
			Speed = maxSpeed;

		x += Speed;
	}
	 
	bool CheckFinish(int finish_distance) {
		if (x >= finish_distance && USKORENIE != 0)
		{
			Speed = 0;
			USKORENIE = 0;
			cout << "Машина " << name << " преодолела финишную черту" << endl;
			return true;
		}
		return false;
	}
};




int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	const int n = 3;
	// Создаем 3 Машины
	Car raceCars[n];

	// race

	for (int i = 0; i < n; i++)
	{
		// Даем каждой случайные характеристи
		raceCars[i].GetRandomCar();
		raceCars[i].name += "_" + to_string(i + 1);
		// И выводим каждую на экран
		raceCars[i].PrintCar();
	}
	// Задаем длинну трассы
	int lenght_of_trace = 10000;
	int c = 0;
	// Пока все машины не преодолеют финишную черту
	while (c < n)
	{
		// Обрабатываем машины
		for (int i = 0; i < n; i++)
		{
			// каждая машина двигается
			raceCars[i].Move();
			// Считаем ее если машина преодолела финишную черту
			if (raceCars[i].CheckFinish(lenght_of_trace))
			{
				c++;
			}
		}
	}
	system("pause");
	return 0;
}
