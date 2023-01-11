#include <SFML/Graphics.hpp>
using namespace sf;
const int W = 1600;
const int H = 1000;
float dist = 50;
float speed = 1;
struct STAR 
{
    float x;
    float y;
    float z;
    STAR() {
        x = rand() % 10000 - 5000;
        y = rand() % 10000 - 5000;
        z = rand() % 10000;
    }
    void move() 
    {
        z -= speed;
        if (z <= 0)
        {
            z = 10000;
            x = rand() % 10000 - 5000;
            y = rand() % 10000 - 5000;
        }
        else if (z > 10000)
        {
            z = 0;
            x = rand() % 10000 - 5000;
            y = rand() % 10000 - 5000;
        }
    }
};
int main()
{
    RenderWindow window(VideoMode(W, H), "SFML works!");
    CircleShape shape(10.f);
    shape.setFillColor(Color::White);

    const int length = 100;
    STAR stars[length];
    bool isHyperDrive = false;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) 
            {
                if (event.key.code == Keyboard::Up)
                    dist--;
                if (event.key.code == Keyboard::Down)
                    dist++;
                if (event.key.code == Keyboard::W)
                    speed += 0.1;
                if (event.key.code == Keyboard::S)
                    speed -= 0.1;
                if (event.key.code == Keyboard::Space)
                    isHyperDrive = !isHyperDrive;

            }
        }
        if(!isHyperDrive) 
            window.clear();

        for (int i = 0; i < length; i++)
        {
            stars[i].move();
            float k = (dist + stars[i].z) / dist;
            float screenX = stars[i].x / k + W / 2;
            float screenY = stars[i].y / k + H / 2;
            shape.setPosition(screenX, screenY);
            float r = -stars[i].z / 1000 + 10;
            shape.setRadius(r > 0 ? r : 0);
            window.draw(shape);
        }

        window.display();
    }

    return 0;
}
