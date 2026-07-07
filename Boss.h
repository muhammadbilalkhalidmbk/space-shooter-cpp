#ifndef BOSS_H
#define BOSS_H

#include "BossBullet.h"
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

class Boss {
private:
    sf::Sprite sprite;
    sf::Texture* texturePtr = nullptr;

    int health;
    float speed;
    bool alive;
    int maxHealth;

public:
    Boss();
    void setTexture(sf::Texture* tex);
    void spawn(int level);
    void update();
    void draw(sf::RenderWindow& window);
    void damage();
    bool isDead() const;
    bool isAlive() const;
    sf::FloatRect getBounds() const;
    int getHealth() const;
    int getMaxHealth() const;
    std::vector<BossBullet> shoot(int level, sf::Texture* bulletTex);

};

#endif
