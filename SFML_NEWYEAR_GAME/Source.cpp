#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
const int W = 1400;
const int H = 800;
struct item
{
    float x;
    float y;

    item() {
        x = rand() % W;
        y = 0;
    }
};

int main()
{
    RenderWindow window(VideoMode(W, H), "SFML works!");
    window.setFramerateLimit(60);
    RectangleShape shape(Vector2f(200, 200));
    shape.setPosition(W / 2, H - shape.getSize().y);
    RectangleShape shape2(Vector2f(50,50));

    Texture texture;
    if (texture.loadFromFile("texture.png"))
    {
        shape.setTexture(&texture);
    }
    Texture texture2;
    if (texture2.loadFromFile("texture2.png"))
    {
        shape2.setTexture(&texture2);
    }

    Font font;
    Text text("0", font);
    text.setCharacterSize(30);
    text.setPosition(0, 0);
    font.loadFromFile("arial.ttf");

    item i;
    int cnt = 0;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) 
            {
                if (event.key.code == Keyboard::Left)
                    shape.move(-5, 0);
                if (event.key.code == Keyboard::Right)
                    shape.move(5, 0);

            }
        }

        i.y+=2;
        if (i.y > H) 
        {
            i.x = rand() % W;
            i.y = 0;
        }
        else if(i.y > shape.getPosition().y 
            and i.y + shape2.getSize().y 
            < shape.getPosition().y + shape.getSize().y
            and i.x > shape.getPosition().x
            and i.x + shape2.getSize().x
            < shape.getPosition().x + shape.getSize().x)
        {
            i.x = rand() % W;
            i.y = 0;
            cnt++;
            text.setString(std::to_string(cnt));
        }
        window.clear();
        window.draw(shape);
        shape2.setPosition(i.x, i.y);
        window.draw(shape2);
        window.draw(text);
        window.display();
    }

    return 0;
}
