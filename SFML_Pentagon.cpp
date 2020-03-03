


/*void Draw()
{
	// Очистка экрана
//	system("cls");
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
//			cout << lifenow[j][i];
		}
		// Перевод на новую строку
		// Чтобы не вывести кадр одной строчкой
//		cout << endl;
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
/*bool Keys()
{	
	// Функция GetKeyState дает много информации о клавише
	// Так как необходимо только узнать, нажата ли она?
	// Необходимо сделать СДВИГ вправо на 7 символов с помощью >> 
	if (GetKeyState(27) >> 7) // Если нажата клавиша
		// с кодом 27 (ESC), то возвращаем ложь 
		return false;
	if (GetKeyState(' ') >> 7)
		Fill();
	return true;
}*//*
int countOfOther(int i, int j)
{
	int cnt = 0;
	//if (lifenow[(i) % X][(j) % Y] != 0) cnt++;
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


// Установка максимального колличества кадров в секунду (FPS) в этом окне = 15
window.setFramerateLimit(15);

// Переменная для отслеживания событий
sf::Event event;
// Пока окно открыто, будет происходить отрисовка
while (window.isOpen())
{
// Обработка событий
while (window.pollEvent(event))
{
// Обработка событий закрытия окна
if (event.type == sf::Event::Closed) window.close();
// Обработка событий нажатия клавишь
if (event.type == sf::Event::KeyPressed)
{
// Получаем нажатую клавишу - выполняем соответствующее действие
if (event.key.code == sf::Keyboard::Escape) window.close();
}
}




*/


//Подключение графической библиотеки SFML
#include <SFML/Graphics.hpp>

int main()
{
	// Сооздание окна размером 600 на 400 с именем "SFML"
	sf::RenderWindow window(sf::VideoMode(600, 400), "SFML");
	window.setFramerateLimit(60);

	sf::CircleShape pentagon(100, 5);
	// Задаем ему белый цвет
	pentagon.setFillColor(sf::Color(255, 255, 255));
	// Задаем ему позицию в на основе x для данного кадра
	pentagon.setPosition(300, 200);
	// Задаем центр
	pentagon.setOrigin(100, 100);

	while(window.isOpen()) {
		// Выполняем необходимые действия по отрисовке
		// Очистка кадра
		window.clear();
	
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
			// Close window: exit
			if (event.type == sf::Event::KeyPressed)
				window.close();
		}
		pentagon.rotate(1);

		window.draw(pentagon);
		// Рисуем кадр
		window.display();
	}
	return 0;
}

