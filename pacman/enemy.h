#pragma once
#include "entity.h"

class Enemy : public Entity {
private:
    float _speed;

public:
    void update(double dt) override;
    Enemy();
    void render(sf::RenderWindow &window) const override;
};