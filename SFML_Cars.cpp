#include <SFML/Graphics.hpp>
#include <string>
struct Car
{
	std::string name = "";
	sf::Color color = sf::Color::Green; // Строка в которой содержится цвет
	int countOfCYLIINDERs = 0;
	int maxSpeed = 0;
	int USKORENIE = 0;
	int price = 0;

	int x = 0;
	int Speed = 0;
};

Car GetRandomCar() {
	Car car;
	sf::Color colors[] = {
		sf::Color::Blue,
		sf::Color::Red,
		sf::Color::Green,
		sf::Color::Yellow,
		sf::Color::Magenta,
		sf::Color::White,
		sf::Color::Cyan

	};
	std::string names[] = {
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

int main()
{

	setlocale(LC_ALL, "Rus");
	srand(time(0));
	const int n = 6;

	Car raceCars[n];

	// race

	for (int i = 0; i < n; i++)
	{
		raceCars[i] = GetRandomCar();
		raceCars[i].name += "_" + std::to_string(i + 1);

	}

	sf::RenderWindow window(sf::VideoMode(1500, 700), "SFML works!");
	window.setFramerateLimit(10);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		int lenght_of_trace = 1200;
		int c = 0;
		
		window.clear();
		sf::RectangleShape line(sf::Vector2f(10, 1000));
		line.setFillColor(sf::Color::White);
		line.setPosition(lenght_of_trace, 0);
		window.draw(line);
		for (int i = 0; i < n; i++)
		{
			sf::RectangleShape rectangle(sf::Vector2f(100, 50));
			rectangle.setFillColor(raceCars[i].color);
			rectangle.setPosition( raceCars[i].x - 50 , 100 * i + 100 );

			window.draw(rectangle);

			raceCars[i].Speed += raceCars[i].USKORENIE;
			if (raceCars[i].Speed > raceCars[i].maxSpeed)
				raceCars[i].Speed = raceCars[i].maxSpeed;

			raceCars[i].x += raceCars[i].Speed;
			if (raceCars[i].x >= lenght_of_trace)
			{
				c++;
				raceCars[i].Speed = 0;
				raceCars[i].x = 0;
			}
		}
		


		
		window.display();
	}

	return 0;
}
