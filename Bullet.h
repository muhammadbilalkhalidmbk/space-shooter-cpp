#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
private:
    sf::Sprite sprite;
    sf::Texture* texturePtr = nullptr;
    float speed;
    bool isCharged = false;

public:
    Bullet(float x, float y, sf::Texture* tex, bool charged = false);  
    void update();
    void draw(sf::RenderWindow& window);
    bool isOffScreen() const;
    sf::FloatRect getBounds() const;

};

#endif
