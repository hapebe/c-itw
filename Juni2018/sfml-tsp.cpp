#include <iostream>
#include <sstream>
#include <cstdlib> // for rand() and srand()
#include <cmath> // for sqrt()
#include <SFML/Graphics.hpp>
#include "sfml-tsp-global.cpp"
#include "sfml-tsp-model.cpp"
#include "sfml-tsp-gfx.cpp"

void init(void) {
    painter = new TSPPainter();

    // create and set up the application's data model:
    createPoints();
    painter->updatePoints(points);

    createRoutingTable();
    cout << routingTable->debug();

    // currentRoute = TSPRouter::naiveOrdered();
    currentRoute = TSPRouter::naiveClosest();
    cout << "Current Route is " << (currentRoute->isComplete()?"complete":"not complete") << "." << endl;
    cout << "Route length: " << currentRoute->getLength() << "." << endl;
    painter->updateRoute(currentRoute);

}

void destroy(void) {
    // clean up after the application:
    deletePoints(); // in sfml-tsp-model.cpp
    deleteRoutingTable();
}

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Travelling Salesman Problem using SFML", sf::Style::Default, settings);

    // sf::CircleShape circle1(100.f);
    // circle1.setFillColor(sf::Color::Red);
    // circle1.move(-100,-100);

    // never use both of the following settings at the same time:
    window.setVerticalSyncEnabled(true); // call it once, after creating the window
    // window.setFramerateLimit(60); // call it once, after creating the window

    window.setKeyRepeatEnabled(false);

    init();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Resized:
                    wWidth = event.size.width;
                    wHeight = event.size.height;
                    std::cout << "new width: " << event.size.width << std::endl;
                    std::cout << "new height: " << event.size.height << std::endl;
                    break;

                // window closed
                case sf::Event::Closed:
                    window.close();
                    destroy();
                    break;

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
                    currentMouseX = event.mouseMove.x;
                    currentMouseY = event.mouseMove.y;
                    highlightedPoint = findClosestPointIdx(
                        screen2coordX(currentMouseX),
                        screen2coordY(currentMouseY)
                    );
//                    std::cout << "mouse (x;y): " << event.mouseMove.x << ";" << event.mouseMove.y << std::endl;
//                    std::cout << "coord (x;y): " << screen2coordX(currentMouseX) << ";" << screen2coordY(currentMouseY) << std::endl;
//                    if (highlightedPoint != -1) {
//                        cout << "Point [" << highlightedPoint << "] is closest to the pointer..." << endl;
//                    }
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

        // clear the window with black color:
        window.clear(sf::Color::Black);

        // window.draw(circle1);

        // paint all points, highlight the point which is closest to the mouse pointer:
        painter->paintPoints(&window, highlightedPoint);

        // draw the current route:
        painter->paintRoute(&window);

        // internally swaps the front and back buffers:
        window.display();

    }

    return 0;
}
