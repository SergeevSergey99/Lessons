#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

struct snow
{
    int x, y;
    int dx, dy;
    snow()
    {
        x = rand() % 1900;
        y = rand() % 1000;

        dx = rand() % 11 - 5;
        dy = 1 + rand() % 5;
    }

    void Move()
    {
        x += dx;
        y += dy;
        if (x > 1920) x = 0;
        if (x < 0) x = 1920;
        if (y > 1080) y = 0;
    }

    void Draw(sf::RenderWindow * window)
    {
        sf::CircleShape shape(5);
        shape.setFillColor(sf::Color::White);
        shape.setPosition(x, y);
        window->draw(shape);
    }
};

int main()
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    window.setFramerateLimit(30);
    
    const int size = 1000;
    snow snows[size];


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (size_t i = 0; i < size; i++)
        {
            snows[i].Move();
            snows[i].Draw(&window);
        }
        window.display();
    }

    return 0;
}