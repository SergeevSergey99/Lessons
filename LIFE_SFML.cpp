#include <SFML/Graphics.hpp>
//колличество элементов по горизонтали
const unsigned int X = 180;
//колличество элементов по вертикали
const unsigned int Y = 90;
//размер клетки
const unsigned int H = 10;
// Массив элементов одного кадра
int lifenow[X][Y] = {};
int lifenext[X][Y] = {};


sf::RenderWindow window(sf::VideoMode((X * H), (Y * H)), "LIFE");

void Draw()
{
	//Построчный вывод слоев кадра
	for (int i = 0; i < Y; i++)
	{
		//Посимвольный вывод одного  слоя кадра
		for (int j = 0; j < X; j++)
		{
			sf::RectangleShape rectangle(sf::Vector2f(H, H));
			if (lifenow[j][i] == 0)
				rectangle.setFillColor(sf::Color(0, 0, 0));
			else
				rectangle.setFillColor(sf::Color(0, 100, 0));
			rectangle.setPosition(j * H, i * H);
			window.draw(rectangle);
		}
	}
}
void Fill()
{
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < X; j++)
		{
			lifenow[j][i] = ((rand() % 3 == 0)?'O':0);
		}
	}
}
int countOfOther(int i, int j)
{
	int cnt = 0;
	if (lifenow[(i - 1) % X][(j) % Y] != 0) cnt++;
	if (lifenow[(i + 1) % X][(j) % Y] != 0) cnt++;
	if (lifenow[(i) % X][(j - 1) % Y] != 0) cnt++;
	if (lifenow[(i - 1) % X][(j - 1) % Y] != 0) cnt++;
	if (lifenow[(i + 1) % X][(j - 1) % Y] != 0) cnt++;
	if (lifenow[(i) % X][(j + 1) % Y] != 0) cnt++;
	if (lifenow[(i - 1) % X][(j + 1) % Y] != 0) cnt++;
	if (lifenow[(i + 1) % X][(j + 1) % Y] != 0) cnt++;
	return cnt;
}
void Swap()
{
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < X; j++)
		{
			lifenow[j][i] = lifenext[j][i];
		}
	}
}
void Update()
{
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < X; j++)
		{
			int cnt = countOfOther(j, i);
			if (cnt < 2 || cnt > 3) lifenext[j][i] = 0;
			if (lifenow[j][i] == 0 && cnt == 3) lifenext[j][i] = 'O';
			if (lifenow[j][i] == 'O' && (cnt == 3 || cnt == 2)) lifenext[j][i] = 'O';
		}

	}
	Swap();
}
int main()
{
	srand(unsigned(0));
	window.setFramerateLimit(60);

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::Space) Fill();
			}
		}



		// Выполняем необходимые действия по отрисовке
		window.clear();
		

		Update();
		Draw();
		window.display();
	}
	
	return 0;
}

