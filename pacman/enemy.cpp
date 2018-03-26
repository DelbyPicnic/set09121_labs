#include "enemy.h"

using namespace sf;
using namespace std;

void Enemy::update(double dt){
    // Move in four directions based on keys

    Entity::update(dt);
}

Enemy::Enemy()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
        _shape->setFillColor(Color::Blue);
        _shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Enemy::render(sf::RenderWindow &window) const {
    window.draw(*_shape);
}