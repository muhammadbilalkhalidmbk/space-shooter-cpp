#include "Bullet.h"

Bullet::Bullet(float x, float y, sf::Texture* tex, bool charged) {
    texturePtr = tex;
    sprite.setTexture(*texturePtr);
    sprite.setPosition(x, y);

    if (charged) {
        sprite.setScale(0.3f, 0.6f);  
        speed = -15.0f;              
    } else {
        sprite.setScale(0.1f, 0.25f);
        speed = -8.0f;
    }
}




void Bullet::update() {
    sprite.move(0, speed);
}


void Bullet::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Bullet::isOffScreen() const {
    return sprite.getPosition().y + sprite.getGlobalBounds().height < 0;
}

sf::FloatRect Bullet::getBounds() const {
    return sprite.getGlobalBounds();
}
