#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;


class Car {
public:
    string name = "";
    int speed = 0;
    int maxSpeed = 0;
    int accel = 0;
    int x = 0;
    sf::Color color;
    Car() {
        x = 0;
        accel = 1 + rand() % 10;
        speed = 0;
        maxSpeed = 250 + rand() % 151;
        color = sf::Color(rand()%256, rand() % 256, rand() % 256,255);
        string names[4] = {
                "Феррари", "Ламборгини", "БМВ", "Лада"
        };

        name = names[rand() % 4];
    }

    void Draw(sf::RenderWindow * window, int y)
    {
        sf::CircleShape shape(20.0, 4);
        shape.setFillColor(color);
        shape.setPosition(x, y);
        window->draw(shape);
    }
    bool isFinished(int finish)
    {
        if(x >= finish)
        {
            return true;
        }
        return false;
    }
    void Move() {
        speed += accel;
        if (speed > maxSpeed)
        {
            speed = maxSpeed;
        }
        x += speed;
    }
    void print() {
        cout << "Имя: " << name << endl;
        cout << "Максимальная скорость: " << maxSpeed << endl;
        cout << "Ускорение: " << accel << endl << endl;
    }
};

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "rus");
    Car cars[10];
    for (int i = 0; i < 10; ++i) {
        cout << i << endl;
        cars[i].print();
    }
    sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!");
    window.setFramerateLimit(1);

    int finish = 900;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (size_t i = 0; i < 10; i++)
        {
            if(!cars[i].isFinished(finish))
            {
                cars[i].Move();
            }
            cars[i].Draw(&window, i * 50);
        }
        window.display();
    }

    return 0;
}