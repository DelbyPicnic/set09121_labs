#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include <iostream>


using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::W, // Player Up
    Keyboard::S, // Player Down
    Keyboard::A, // Player Left
    Keyboard::D  // Player Right
};

EntityManager* em = new EntityManager();

void Load()
{
    /*
    ls::loadLevelFile("res/maze_2.txt");

    // Print the level to the console
    for (size_t y = 0; y < ls::getHeight(); ++y){
        for (size_t x = 0; x < ls::getWidth(); ++x){
            cout << ls::getTile({x, y});
        }
        cout << endl;
    }
    */

    Player* pl = new Player();
    Enemy* enm = new Enemy();

    em.list.push_back(pl);
    em.list.push_back(enm);
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
    Load();
    int screenWidth = 8 * 100;
    int screenHeight = 8 * 100;
    RenderWindow window(VideoMode(screenWidth, screenHeight ), "Tiles");


    while(window.isOpen()){
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }

    return 0;
}