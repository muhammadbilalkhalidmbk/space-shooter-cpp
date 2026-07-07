#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#include <SFML/Graphics.hpp>

class EnemyBullet {
private:
    sf::Sprite sprite;
    sf::Texture* texturePtr = nullptr;
    float speed;

public:
    EnemyBullet(float x, float y, sf::Texture* tex);
    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isOffScreen() const;
};

#endif
