#include <SFML/Graphics.hpp>
#include <iostream>

bool IsCollision(const sf::CircleShape& shape, const sf::Vector2i& target);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 200), "SFML works!");
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        // 이벤트가 쌓여있으면 다 처리를 하고 루프를 빠져나옴 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update 하는 곳

        const auto& pos = shape.getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            shape.setPosition(pos + sf::Vector2f(0.0f, -0.1f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            shape.setPosition(pos + sf::Vector2f(0.0f, +0.1f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            shape.setPosition(pos + sf::Vector2f(-0.1f, 0.0f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            shape.setPosition(pos + sf::Vector2f(+0.1f, 0.0f));
        }

        const auto& mpos = sf::Mouse::getPosition();
        if (mpos.x >= 0 && mpos.x <= 1000 && mpos.y >= 0 && mpos.y <= 200)
        {
            if (IsCollision(shape, mpos))
            {
                std::cout << "원 내부" << std::endl;
            }
        }
        window.clear();
        /* 그리는 작업 시작*/
        // 메모리에 그리는 작업
        window.draw(shape);
        // 메모리에 있는 모든 오브젝트를 표시
        /* 그리는 작업 루프*/
        window.display();
    }

    return 0;
}

bool IsCollision(const sf::CircleShape& shape, const sf::Vector2i& target)
{
    auto pos = shape.getPosition();
    pos.x = pos.x + shape.getRadius();
    pos.y = pos.y + shape.getRadius();
    sf::Vector2f v = sf::Vector2f(target.x, target.y) - pos;
    float distance_2 = v.x * v.x + v.y * v.y;
    float radius_2 = shape.getRadius() * shape.getRadius();

    return distance_2 <= radius_2;
}
