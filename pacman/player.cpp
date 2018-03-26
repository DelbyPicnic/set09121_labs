#include "player.h"

using namespace sf;
using namespace std;

void Player::update(double dt){
    // Move in four directions based on keys

    Entity::update(dt);
}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
        _shape->setFillColor(Color::Yellow);
        _shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Player::render(sf::RenderWindow &window) const {
    window.draw(*_shape);
}