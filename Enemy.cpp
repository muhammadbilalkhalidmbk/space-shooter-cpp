#include "Enemy.h"
#include <cmath>
#include <cstdlib>

Enemy::Enemy(float x, float y) {
    sprite.setPosition(x, y);
    sprite.setScale(0.07f, 0.07f); 
    speed = 1.0f;
    health = 1;
    movingRight = true;
}

void Enemy::setSpeed(float s) {
    speed = s;
}

void Enemy::setHealth(int h) {
    health = h;
}

void Enemy::damage() {
    health--;
}

bool Enemy::isDead() const {
    return health <= 0;
}

sf::Vector2f Enemy::getPosition() const {
    return sprite.getPosition();
}

void Enemy::move() {
    if (movingRight)
        sprite.move(speed, 0);
    else
        sprite.move(-speed, 0);
}

void Enemy::reverseAndDrop() {
    movingRight = !movingRight;
    sprite.move(0, 20); 
}

void Enemy::update() {
    move();
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Enemy::getBounds() const {
    return sprite.getGlobalBounds();
}

void Enemy::reset() {
    float x = static_cast<float>(rand() % 760);
    sprite.setPosition(x, -20);
}

void Enemy::setTexture(sf::Texture* tex) {
    texturePtr = tex;
    sprite.setTexture(*texturePtr);
}
