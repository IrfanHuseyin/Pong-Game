#include <SFML/Graphics.hpp>
#include <cmath>
#include <sstream>

int main()
{
    // Create window
    sf::VideoMode vm(1920, 1080);
    sf::RenderWindow window(vm, "Pong Game By IF", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);

    sf::Font font;

    font.loadFromFile("Fonts/DS-DIGI.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setPosition(200, 10);

    font.loadFromFile("Fonts/DS-DIGI.ttf");
    sf::Text text2;
    text2.setFont(font);
    text2.setCharacterSize(50);
    text2.setFillColor(sf::Color::Blue);
    text2.setPosition(1720, 10);

    int player1Score = 0;
    int player2Score = 0;
    
    // Ball
    sf::CircleShape ball(15.f);
    ball.setOrigin(7.5f, 7.5f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(1920 / 2 - 7.5, 1080 / 2 - 7.5);

    // Paddle 1
    sf::RectangleShape paddle1(sf::Vector2f(20.f, 150.f));
    paddle1.setFillColor(sf::Color::Red);
    paddle1.setPosition(20, 1080 / 2 - 75);

    // Paddle 2
    sf::RectangleShape paddle2(sf::Vector2f(20.f, 150.f));
    paddle2.setFillColor(sf::Color::Blue);
    paddle2.setPosition(1880, 1080 / 2 - 75);

    // Set initial velocity of the ball
    float speed = 0.15f;
    float angle = 45.f; // Angle in degrees
    float vx = speed * cos(angle * 3.14159265f / 180.f); // Horizontal velocity
    float vy = speed * sin(angle * 3.14159265f / 180.f); // Vertical velocity

    sf::Clock clock;

    while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move ball
        ball.move(vx, vy);

        // Reverse vertical velocity if ball hits top or bottom of window
        if (ball.getPosition().y < 0.f || ball.getPosition().y > 1050.f)
            vy = -vy;

        // Reverse horizontal velocity if ball hits left or right side of window 
        if (ball.getPosition().x > paddle2.getPosition().x)                 
        { 
            ball.setPosition(1920 / 2 - 7.5, 1080 / 2 - 7.5);
            vy = -vy;
            player1Score++;
        }
        else if (ball.getPosition().x < paddle1.getPosition().x)
        {
            ball.setPosition(1920 / 2 - 7.5, 1080 / 2 - 7.5);
            vy = -vy;
            player2Score++;
        }

        // Check for collision between ball and paddle1
        if (ball.getPosition().x < paddle1.getPosition().x + paddle1.getSize().x &&
            ball.getPosition().y > paddle1.getPosition().y &&
            ball.getPosition().y < paddle1.getPosition().y + paddle1.getSize().y)
        {
            float relativeIntersectY = (paddle1.getPosition().y + (paddle1.getSize().y / 2.f)) - ball.getPosition().y;
            float normalizedRelativeIntersectionY = relativeIntersectY / (paddle1.getSize().y / 2.f);
            float bounceAngle = normalizedRelativeIntersectionY * (-30.f * 3.14159265f / 180.f);
            vx = speed * cos(bounceAngle);
            vy = speed * sin(bounceAngle);
        }

        // Check for collision between ball and paddle2
        if (ball.getPosition().x + ball.getRadius() > paddle2.getPosition().x &&
            ball.getPosition().y > paddle2.getPosition().y &&
            ball.getPosition().y < paddle2.getPosition().y + paddle2.getSize().y)
        {
            float relativeIntersectY = (paddle2.getPosition().y + (paddle2.getSize().y / 2.f)) - ball.getPosition().y;
            float normalizedRelativeIntersectionY = relativeIntersectY / (paddle2.getSize().y / 2.f);
            float bounceAngle = normalizedRelativeIntersectionY * (30.f * 3.14159265f / 180.f) + (180.f * 3.14159265f / 180.f);
            vx = speed * cos(bounceAngle);
            vy = speed * sin(bounceAngle);
        }

        // Paddle1 movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if (paddle1.getPosition().y > 0) 
            {
                paddle1.move(0, -0.1);
            }
        }
		    
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (paddle1.getPosition().y < 930) 
            {
                paddle1.move(0, 0.1);
            }
        }       

        // Paddle2 movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	    {
            if (paddle2.getPosition().y > 0) 
            {
                paddle2.move(0, -0.1);
            }
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (paddle2.getPosition().y < 930) 
            {
                paddle2.move(0, 0.1);
            }
        }

        // Player 1 score display
	    std::stringstream ss;
	    ss << player1Score << std::endl;
	    text.setString(ss.str());

        // Player 2 score display
        std::stringstream ss2;
        ss2 << player2Score << std::endl;
        text2.setString(ss2.str());

        window.clear();
        window.draw(text);
        window.draw(text2);
        window.draw(ball);
        window.draw(paddle1);
        window.draw(paddle2);
        window.display();

    }

    return 0;

}