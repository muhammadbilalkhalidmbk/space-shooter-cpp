#ifndef BOSS_BULLET_H
#define BOSS_BULLET_H

#include <SFML/Graphics.hpp>

class BossBullet {
private:
    sf::Sprite sprite;
    sf::Texture* texturePtr = nullptr;
    float speed;
    float dx;

public:
    BossBullet(float x, float y, float dxVal, sf::Texture* tex);
    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isOffScreen() const;
};

#endif
