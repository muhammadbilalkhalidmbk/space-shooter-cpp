#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(float x, float y, sf::Texture* tex) {
    texturePtr = tex;
    sprite.setTexture(*texturePtr);
    sprite.setPosition(x, y);
    sprite.setScale(0.1f, 0.1f);  
    speed = 5.0f;
}

void EnemyBullet::update() {
    sprite.move(0, speed);
}

void EnemyBullet::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool EnemyBullet::isOffScreen() const {
    return sprite.getPosition().y > 600;
}

sf::FloatRect EnemyBullet::getBounds() const {
    return sprite.getGlobalBounds();
}
