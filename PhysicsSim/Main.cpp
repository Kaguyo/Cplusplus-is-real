#include <SFML/Graphics.hpp>
#include <iostream>

/* Diversas keywords de Event::KeyPressed.
if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
{
    if (keyPressed->scancode == sf::Keyboard::Scan::Escape)
    {
        std::cout << "the escape key was pressed" << std::endl;
        std::cout << "scancode: " << static_cast<int>(keyPressed->scancode) << std::endl;
        std::cout << "code: " << static_cast<int>(keyPressed->code) << std::endl;
        std::cout << "control: " << keyPressed->control << std::endl;
        std::cout << "alt: " << keyPressed->alt << std::endl;
        std::cout << "shift: " << keyPressed->shift << std::endl;
        std::cout << "system: " << keyPressed->system << std::endl;
        std::cout << "description: " << sf::Keyboard::getDescription(keyPressed->scancode).toAnsiString() << std::endl;
        std::cout << "localize: " << static_cast<int>(sf::Keyboard::localize(keyPressed->scancode)) << std::endl;
        std::cout << "delocalize: " << static_cast<int>(sf::Keyboard::delocalize(keyPressed->code)) << std::endl;
    }
}
*/
/* Diversas keywords de Event::MouseWheelScroll.
if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
{
    switch (mouseWheelScrolled->wheel)
    {
        case sf::Mouse::Wheel::Vertical:
            std::cout << "wheel type: vertical" << std::endl;
            break;
        case sf::Mouse::Wheel::Horizontal:
            std::cout << "wheel type: horizontal" << std::endl;
            break;
    }
    std::cout << "wheel movement: " << mouseWheelScrolled->delta << std::endl;
    std::cout << "mouse x: " << mouseWheelScrolled->position.x << std::endl;
    std::cout << "mouse y: " << mouseWheelScrolled->position.y << std::endl;
}
    MouseButtonPressed / Released
    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseButtonPressed->button == sf::Mouse::Button::Right)
        {
            std::cout << "the right button was pressed" << std::endl;
            std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
            std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;
        }
    }
*/

int main()
{   
    unsigned int windowWidth = 1024, windowHeight = 768;
    sf::Vector2<float> axis ((float)windowWidth / 2, (float)windowHeight / 2);

    // sf::RenderWindow window(sf::VideoMode::getFullscreenModes().at(0), "Physics Simulation", sf::State::Fullscreen);
    sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "Physics Simulation");
    sf::CircleShape circleShape(15.f);
    circleShape.setFillColor(sf::Color::White);
    circleShape.setPosition(axis);
    
    sf::Clock clock;
    sf::Time programElapsedTime;

    // window.setKeyRepeatEnabled(false); // Desativar macro / hold key down

    while (window.isOpen())
    {
        programElapsedTime = clock.getElapsedTime();
        // std::cout << programElapsedTime.asMilliseconds() << std::endl;
        while (const std::optional event = window.pollEvent())
        {   
            if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                std::cout << "new mouse x: " << mouseMoved->position.x << std::endl;
                std::cout << "new mouse y: " << mouseMoved->position.y << std::endl;
            }
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {   
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
            else if (event->is<sf::Event::Resized>())
            {
                auto [Largura, Altura] = window.getSize();
                windowWidth = Largura;
                windowHeight = Altura;
                std::cout << windowWidth << "x" << windowHeight << std::endl;
            }
            if (event->is<sf::Event::FocusLost>())
            {
                // myGame.pause();
            }
            if (event->is<sf::Event::FocusGained>())
            {
                // myGame.resume();
            }
            if (const auto* textEntered = event->getIf<sf::Event::TextEntered>())
            {
                if (textEntered->unicode < 128)
                {
                    // std::cout << "ASCII character typed: " << static_cast<char>(textEntered->unicode) << std::endl;
                }
            }
        }

        window.clear();
        window.draw(circleShape);
        window.display();
    }
}