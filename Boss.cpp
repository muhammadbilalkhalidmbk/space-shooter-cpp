#include "Boss.h"

Boss::Boss() {
    alive = false;
    health = 0;
    speed = 0;
    maxHealth = 0;
    sprite.setScale(0.25f, 0.25f); 
}

void Boss::setTexture(sf::Texture* tex) {
    texturePtr = tex;
    sprite.setTexture(*texturePtr);
}

void Boss::spawn(int level) {
    sprite.setPosition(350, -100);

    if (level == 1) {
        health = 20;
        speed = 0.5f;
    } else if (level == 2) {
        health = 35;
        speed = 0.7f;
    } else if (level == 3) {
        health = 50;
        speed = 1.0f;
    }

    maxHealth = health;
    alive = true;
}

void Boss::update() {
    if (!alive) return;
    sprite.move(0, speed);
    if (sprite.getPosition().y > 100)
        sprite.setPosition(sprite.getPosition().x, 100); 
}

void Boss::draw(sf::RenderWindow& window) {
    if (alive)
        window.draw(sprite);
}

void Boss::damage() {
    if (alive) {
        health--;
        if (health <= 0) {
            alive = false;
        }
    }
}

bool Boss::isDead() const {
    return !alive;
}

bool Boss::isAlive() const {
    return alive;
}

sf::FloatRect Boss::getBounds() const {
    return sprite.getGlobalBounds();
}

int Boss::getHealth() const {
    return health;
}

int Boss::getMaxHealth() const {
    return maxHealth;
}

std::vector<BossBullet> Boss::shoot(int level, sf::Texture* bulletTex) {
    std::vector<BossBullet> shots;

    float x = sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - 5;
    float y = sprite.getPosition().y + sprite.getGlobalBounds().height;

    shots.emplace_back(x, y, 0.0f, bulletTex);

    if (level >= 2) {
        shots.emplace_back(x - 20, y, -1.f, bulletTex);
        shots.emplace_back(x + 20, y, 1.f, bulletTex);
    }

    if (level >= 3) {
        static float angle = 0.f;
        for (int i = 0; i < 4; ++i) {
            float dx = cos(angle + i) * 1.5f;
            shots.emplace_back(x, y, dx, bulletTex);
        }
        angle += 0.1f;
    }

    return shots;
}
