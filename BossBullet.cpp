#include "BossBullet.h"

BossBullet::BossBullet(float x, float y, float dxVal, sf::Texture* tex) {
    texturePtr = tex;
    sprite.setTexture(*texturePtr);
    sprite.setPosition(x, y);
    sprite.setScale(0.15f, 0.15f); 
    speed = 4.5f;
    dx = dxVal;
}

void BossBullet::update() {
    sprite.move(dx, speed);
}

void BossBullet::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect BossBullet::getBounds() const {
    return sprite.getGlobalBounds();
}

bool BossBullet::isOffScreen() const {
    return sprite.getPosition().y > 600;
}
