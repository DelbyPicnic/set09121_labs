#include <SFML/Graphics.hpp>
#include "ship.h"
#include "game.h"
#include <iostream>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::A,    // Player1 Up
    Keyboard::Z,    // Player1 Down
    Keyboard::Up,   // Player2 Up
    Keyboard::Down  // Player2 Down
};

vector<Ship *> ships;
sf::Texture spritesheet;

void Load(){
    if(!spritesheet.loadFromFile("bin/res/img/invaders_sheet.png")){
        cerr << "Failed to load spritesheet!" << endl;
    }
    
    Invader* inv = new Invader(IntRect(0,0,32,32), {100,100});
    ships.push_back(inv);
}

void Update(RenderWindow &window){
    // Reset the clock and recalculate the delta
    static Clock clock;
    float dt = clock.restart().asSeconds();
    // Check and consume events
    Event event;

    while(window.pollEvent(event)){
        if (event.type == Event::Closed){
            window.close();
            return;
        }
    }
    // Close game on escape key
    if (Keyboard::isKeyPressed(Keyboard::Escape)){
        window.close();
    }

    // Call update method for all ships
    for (auto &s : ships){
        s->Update(dt);
    }
}

void Render(RenderWindow &window){
    // Render all ships
    for (const auto s : ships){
        window.draw(*s);
    }
}

int main(){
    RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
    Load();

    while(window.isOpen()){
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}
