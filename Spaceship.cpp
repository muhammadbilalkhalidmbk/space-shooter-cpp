#include "Spaceship.h"

Spaceship::Spaceship() {
    speed = 5.0f;

    leftDrone.setRadius(8);
    leftDrone.setFillColor(sf::Color::Cyan);
    leftDrone.setOrigin(8, 8);

    rightDrone.setRadius(8);
    rightDrone.setFillColor(sf::Color::Cyan);
    rightDrone.setOrigin(8, 8);
}


void Spaceship::moveLeft() {
    if (sprite.getPosition().x > 0)
        sprite.move(-speed, 0);
}

void Spaceship::moveRight() {
    if (sprite.getPosition().x + sprite.getGlobalBounds().width < 800)
        sprite.move(speed, 0);
}

void Spaceship::update() {
    if (hasDrone) {
        float shipX = sprite.getPosition().x;
        float shipY = sprite.getPosition().y;
        float shipWidth = sprite.getGlobalBounds().width;

        leftDrone.setPosition(shipX - 10, shipY + 10);
        rightDrone.setPosition(shipX + shipWidth + 10, shipY + 10);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    if (!isCharging) {
        isCharging = true;
        chargeClock.restart();
    } else {
        if (chargeClock.getElapsedTime().asSeconds() >= 2.0f)
            chargedShotReady = true;
    }
} else {
    isCharging = false;
}

}

void Spaceship::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    if (hasDrone) {
        window.draw(leftDrone);
        window.draw(rightDrone);
    }
}

void Spaceship::shoot(bool charged) {
    float x = sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - 2.5f;
    float y = sprite.getPosition().y;

    if (hasMultiGun) {
        bullets.emplace_back(x - 15, y, bulletTexturePtr, charged);
        bullets.emplace_back(x, y, bulletTexturePtr, charged);
        bullets.emplace_back(x + 15, y, bulletTexturePtr, charged);
    } else {
        bullets.emplace_back(x, y, bulletTexturePtr, charged);
    }

    if (hasDrone) {
        bullets.emplace_back(x - 30, y, bulletTexturePtr, charged);
        bullets.emplace_back(x + 30, y, bulletTexturePtr, charged);
    }
}


std::vector<Bullet>& Spaceship::getBullets() {
    return bullets;
}

sf::FloatRect Spaceship::getBounds() const {
    return sprite.getGlobalBounds();
}

void Spaceship::enableMultiGun(bool enable) {
    hasMultiGun = enable;
}

void Spaceship::enableDrone(bool enable) {
    hasDrone = enable;
}

bool Spaceship::isMultiGunEnabled() const {
    return hasMultiGun;
}

bool Spaceship::isDroneEnabled() const {
    return hasDrone;
}
void Spaceship::setTexture(sf::Texture* tex) {
    texturePtr = tex;
    sprite.setTexture(*texturePtr);
    sprite.setPosition(370, 475); 
    sprite.setScale(0.3f, 0.3f); 
}
void Spaceship::setBulletTexture(sf::Texture* tex) {
    bulletTexturePtr = tex;
}

