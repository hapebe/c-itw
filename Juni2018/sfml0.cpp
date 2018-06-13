#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    shape.move(40,60);

    // never use both of the following settings at the same time:
    window.setVerticalSyncEnabled(true); // call it once, after creating the window
    // window.setFramerateLimit(60); // call it once, after creating the window

    window.setKeyRepeatEnabled(false);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Resized:
                    std::cout << "new width: " << event.size.width << std::endl;
                    std::cout << "new height: " << event.size.height << std::endl;
                    break;

                // window closed
                case sf::Event::Closed: window.close(); break;

                // key pressed
                case sf::Event::KeyPressed:
                    std::cout << "key pressed: " << event.key.code << std::endl;
                    break;

                // mouse events
                case sf::Event::MouseEntered:
                    std::cout << "the mouse cursor has entered the window" << std::endl; break;

                case sf::Event::MouseLeft:
                    std::cout << "the mouse cursor has left the window" << std::endl; break;

                case sf::Event::MouseMoved:
                    std::cout << "new mouse (x;y): " << event.mouseMove.x << ";" << event.mouseMove.y << std::endl;
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        std::cout << "the right button was pressed @ ";
                        std::cout << event.mouseButton.x << ";" << event.mouseButton.y << std::endl;
                    }
                    break;

                // text entered
                case sf::Event::TextEntered:
                    if (event.text.unicode < 128)
                        std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
                    break;

                // we don't process other types of events
                default: break;
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
