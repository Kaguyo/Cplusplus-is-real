#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cstdlib>

// new second option for events processing via: sf::Window::handleEvents
    // const auto onClose = [&window](const sf::Event::Closed&)
    // {
    //     window.close();
    // };
    // const auto onKeyPressed = [&window](const sf::Event::KeyPressed& keyPressed)
    // {
    //     if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
    //         window.close();
    // };

int main() 
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode({800, 600}, 24), "SFML Particle Simulation");
    /*  sf::RenderWindow:: nomeDaWindow(sf::VideoMode::getFullscreenModes().at(0), "Title",
        sf::State::Fullscreen;) 
        
        Assim para criar janela full Screen
    */

    // Set the frame rate limit (optional)
    window.setFramerateLimit(120);

    // Main loop
    while (window.isOpen()) 
    {
        // follows at line below, second option for events processing 
        // window.handleEvents(onClose, onKeyPressed);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            } 
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();
                }
            }
        }

        window.display();
    }

    return 0;
}


