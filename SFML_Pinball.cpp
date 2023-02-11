#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 800), "SFML works!");
    window.setFramerateLimit(60);

    RectangleShape myPlatform(Vector2f(200, 30));
    myPlatform.setFillColor(Color::Green);
    myPlatform.setOrigin(100, 15);
    myPlatform.setPosition(400, 740);

    RectangleShape enemyPlatform(Vector2f(200, 30));
    enemyPlatform.setFillColor(Color::Red);
    enemyPlatform.setOrigin(100, 15);
    enemyPlatform.setPosition(400, 60);

    CircleShape ball(40, 10);
    ball.setFillColor(Color::Blue);
    ball.setOrigin(ball.getRadius(), ball.getRadius());
    ball.setPosition(400, 400);
    float dx = 5, dy = -5;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                    window.close();
                if (event.key.code == Keyboard::Left)
                    myPlatform.move(-10, 0);
                if (event.key.code == Keyboard::Right)
                    myPlatform.move(10, 0);

            }
        }

        if (ball.getPosition().x >= 800 - ball.getRadius())
            dx = -5;
        if (ball.getPosition().x <= 0 + ball.getRadius())
            dx = 5;
        if (ball.getPosition().y <= 
            enemyPlatform.getPosition().y + enemyPlatform.getSize().y/2 + ball.getRadius())
            dy = 5;
        if (ball.getPosition().y >= 800 - ball.getRadius())
            break;

        if (ball.getPosition().y + ball.getRadius() >=
            myPlatform.getPosition().y - myPlatform.getSize().y / 2
            and
            ball.getPosition().y + ball.getRadius() <=
            myPlatform.getPosition().y + myPlatform.getSize().y / 2
            and
            ball.getPosition().x <=
            myPlatform.getPosition().x + myPlatform.getSize().x / 2
            and
            ball.getPosition().x >=
            myPlatform.getPosition().x - myPlatform.getSize().x / 2
            )
            dy = -5;

        ball.move(dx, dy);
        if (enemyPlatform.getPosition().x - enemyPlatform.getSize().x / 2
            >= ball.getPosition().x)
            enemyPlatform.move(-5, 0);
        if (enemyPlatform.getPosition().x + enemyPlatform.getSize().x / 2
            <= ball.getPosition().x)
            enemyPlatform.move(5, 0);

        window.clear(Color::White);
        window.draw(myPlatform);
        window.draw(enemyPlatform);
        window.draw(ball);
        window.display();
    }

    return 0;
}