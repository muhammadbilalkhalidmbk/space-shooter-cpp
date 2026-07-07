#include "PowerUp.h"

PowerUp::PowerUp(float x, float y, PowerUpType t, sf::Texture* tex) : type(t), texturePtr(tex) {
    sprite.setTexture(*texturePtr);
    sprite.setPosition(x, y);
    speed = 2.0f;
    sprite.setScale(0.2f, 0.2f); 
}


void PowerUp::update() {
    sprite.move(0, speed);
}

void PowerUp::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect PowerUp::getBounds() const {
    return sprite.getGlobalBounds();
}

PowerUpType PowerUp::getType() const {
    return type;
}

bool PowerUp::isOffScreen() const {
    return sprite.getPosition().y > 600;
}
