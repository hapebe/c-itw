#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "sfml-tsp-model.cpp"

int wWidth = 750;
int wHeight = 750;

int currentMouseX = -1;
int currentMouseY = -1;

int highlightedPoint = -1;

vector<sf::CircleShape> gfxPoints(TSP_N);

const sf::Color getRandomColor(void) {
    int rnd = rand() % 8;
    switch(rnd) {
        case 0: return sf::Color::Blue;
        case 1: return sf::Color::Green;
        case 2: return sf::Color::Red;
        case 3: return sf::Color::Magenta;
        case 4: return sf::Color::White;
        case 5: return sf::Color::Cyan;
        case 6: return sf::Color::Yellow;
        case 7: return sf::Color(127,127,127);
    }
    return sf::Color::White;
}

int coord2screenX(double x) {
    return x * (wWidth/2) + wWidth/2;
}

int coord2screenY(double y) {
    return y * (wHeight/2) + wHeight/2;
}

double screen2coordX(int x) {
    return ((double)x - (wWidth/2)) / (wWidth/2);
}

double screen2coordY(int y) {
    return ((double)y - (wHeight/2)) / (wHeight/2);
}


void init(void) {
    // create and set up the application's data model:
    createPoints();
    createRoutingTable();
    cout << routingTable->debug();


    vector<TSPPoint>::iterator i;
    int idx=0;
    for(i=points.begin(); i!=points.end(); ++i) {
        cout << (*i) << endl;
        sf::CircleShape s(5.f);
        s.setFillColor(getRandomColor());
        s.move(-5, -5); // move center to 0;0
        s.move(
            coord2screenX((*i).getX()),
            coord2screenY((*i).getY())
        );
        try{
            gfxPoints.at(idx) = s;
        } catch(out_of_range ex) {
            cout << ex.what() << endl;
        }
        idx++;
    }
}

void destroy(void) {
    // clean up after the application:
    deletePoints(); // in sfml-tsp-model.cpp
    deleteRoutingTable();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Travelling Salesman Problem using SFML");

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

        // highlight the point which is closest to the mouse pointer:
        if (highlightedPoint != -1) {
            gfxPoints[highlightedPoint].setRadius(20);
            gfxPoints[highlightedPoint].move(-15,-15);
        }

        // draw the TSP points
        vector<sf::CircleShape>::const_iterator i;
        for(i=gfxPoints.begin(); i!=gfxPoints.end(); ++i) {
            window.draw(*i);
        }

        // internally swaps the front and back buffers:
        window.display();

        // reset the highlighted point to normal size:
        if (highlightedPoint != -1) {
            gfxPoints[highlightedPoint].setRadius(5);
            gfxPoints[highlightedPoint].move(15,15);
        }

    }

    return 0;
}
