#include "ship.h"
#include "game.h"
using namespace sf;
using namespace std;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite(){
    _sprite = ir;
    setTexture(spritesheet);
    setTextureRect(_sprite);
};

Invader::Invader() : Ship(){}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir){
    setOrigin(16, 16);
    setPosition(pos);
}

void Ship::Update(const float &dt){}
void Invader::Update(const float &dt){
    Ship::Update(dt);
}

Ship::~Ship() = default;
