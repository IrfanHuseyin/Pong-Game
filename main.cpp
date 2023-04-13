#include <SFML/Graphics.hpp>
#include <cmath>
#include <sstream>

int main()
{
    const int width = 960;
    const int height = 540;

    sf::VideoMode vm(width, height);
    sf::RenderWindow window(vm, "Pong Game By IF");
    window.setMouseCursorVisible(false);

    sf::Font font;
    font.loadFromFile("Fonts/DS-DIGI.TTF");

    const int textSize = 50;
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(textSize);
    text.setFillColor(sf::Color::Red);
    text.setPosition(width/10, 10);

    sf::Text text2;
    text2.setFont(font);
    text2.setCharacterSize(textSize);
    text2.setFillColor(sf::Color::Blue);
    text2.setPosition(9*width/10 -textSize/2, 10);

    int player1Score = 0;
    int player2Score = 0;
    
    // Ball
    const int radius = 15;
    sf::CircleShape ball(radius);
    ball.setOrigin(ball.getRadius(), ball.getRadius());
    ball.setFillColor(sf::Color::White);
    ball.setPosition(width/2, height/2);

    const float paddleWidth = 20.f;
    const float paddleHeight = 150.f;

    // Paddle 1
    sf::RectangleShape paddle1(sf::Vector2f(paddleWidth, paddleHeight));
    paddle1.setFillColor(sf::Color::Red);
    paddle1.setPosition(paddle1.getSize().x, height/2 - paddle1.getSize().y/2);

    // Paddle 2
    sf::RectangleShape paddle2(sf::Vector2f(paddleWidth, paddleHeight));
    paddle2.setFillColor(sf::Color::Blue);
    paddle2.setPosition(width - 2*paddle2.getSize().x, height/2 - paddle2.getSize().y/2);

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
        if (ball.getPosition().y -ball.getRadius() < 0 || ball.getPosition().y > height - ball.getRadius())
            vy = -vy;

        // Reverse horizontal velocity if ball hits left or right side of window 
        if (ball.getPosition().x > paddle2.getPosition().x)                 
        { 
            ball.setPosition(width/2, height/2);
            vy = -vy;
            player1Score++;
        }
        else if (ball.getPosition().x < paddle1.getPosition().x)
        {
            ball.setPosition(width/2, height/2);
            vy = -vy;
            player2Score++;
        }

        // Check for collision between ball and paddle1
        if (ball.getPosition().x-ball.getRadius() < paddle1.getPosition().x + paddle1.getSize().x &&
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
                paddle1.move(0, -speed);
            }
        }
		    
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (paddle1.getPosition().y < height-paddle1.getSize().y) 
            {
                paddle1.move(0, speed);
            }
        }       

        // Paddle2 movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	    {
            if (paddle2.getPosition().y > 0) 
            {
                paddle2.move(0, -speed);
            }
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (paddle2.getPosition().y < height -paddle2.getSize().y) 
            {
                paddle2.move(0, speed);
            }
        }

        // Player 1 score display
	    std::stringstream ss;
	    ss << player1Score;
	    text.setString(ss.str());

        // Player 2 score display
        std::stringstream ss2;
        ss2 << player2Score;
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
