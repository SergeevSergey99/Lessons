#include <SFML/Graphics.hpp>
#define X 1920
#define Y 1080
#define STARCOUNT 200
using namespace sf;

int offset = 20;
class Star
{
    float x, y, z;
    float radius = 1;
    CircleShape shape;

public:
    Star()
    {
        x = rand() % 2001 - 1000;
        x *= 4;
        y = rand() % 2001 - 1000;
        y *= 4;
        z = rand() % 201;
        shape.setFillColor(Color::White);
    }

    void Move() 
    {
        z-= 0.5;
        if(z <= 0)
        {
            x = rand() % 2001 - 1000;
            x *= 4;
            y = rand() % 2001 - 1000;
            y *= 4;
            z = 200;
        }
    }
    void Draw(RenderWindow * window)
    {
        shape.setRadius(radius + (200 - z) * 0.03);
        int screenX = x*100 / (z*100 + offset) * offset + X / 2;
        int screenY = y*100 / (z*100 + offset) * offset + Y / 2;
        shape.setPosition(screenX, screenY);
        window->draw(shape);
    }
};
int main()
{
    RenderWindow window(VideoMode(X, Y), "SFML works!", Style::Fullscreen);
    window.setFramerateLimit(50);

    Star stars[STARCOUNT];

    bool hyper = false;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed and event.key.code == Keyboard::Escape)
                window.close();
            if (event.type == Event::KeyPressed and event.key.code == Keyboard::Space)
                hyper = !hyper;

        }

        if(!hyper)
           window.clear();

        for(int i = 0; i < STARCOUNT; i++)
        {
            stars[i].Move();
            stars[i].Draw(&window);
        }

        window.display();
    }

    return 0;
}