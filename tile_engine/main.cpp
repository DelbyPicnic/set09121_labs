#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include <iostream>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::W, // Player Up
    Keyboard::S, // Player Down
    Keyboard::A, // Player Left
    Keyboard::D  // Player Right
};

vector<Entity *> entities;

void Load()
{
    Player* pl = new Player();
    entities.push_back(pl);
}

void Update(RenderWindow &window)
{
    static Clock clock;
    float dt = clock.restart().asSeconds();

    Event evt;

    while(window.pollEvent(evt)){
        if (evt.type == Event::Closed){
            window.close();
            return;
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape)){
        window.close();
    }

    if (Keyboard::isKeyPressed(controls[0])){
        entities[0]->move(Vector2f(0.0f, -1.0f));
    }
    if (Keyboard::isKeyPressed(controls[1])){
        entities[0]->move(Vector2f(0.0f, 1.0f));
    }
    if (Keyboard::isKeyPressed(controls[2])){
        entities[0]->move(Vector2f(-1.0f, 0.0f));
    }
    if (Keyboard::isKeyPressed(controls[3])){
        entities[0]->move(Vector2f(1.0f, 0.0f));
    }
    

    for(auto &ent : entities){
        ent->update(dt);
    }
}

void Render(RenderWindow &window)
{
    for(const auto &ent : entities){
        ent->render(window);
    }
}

int main()
{
    RenderWindow window(VideoMode(640, 480), "Tiles");
    Load();

    while(window.isOpen()){
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }

    return 0;
}