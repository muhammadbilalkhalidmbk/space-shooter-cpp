#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
private:
    sf::Sprite sprite;
    sf::Texture* texturePtr = nullptr;
    float speed;
    int health;
    bool movingRight;


public:
    Enemy(float x, float y);
    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void reset();
    void setSpeed(float s);
    void setHealth(int h);
    void damage();
    bool isDead() const;
    sf::Vector2f getPosition() const;
    void move();
    void reverseAndDrop();
    void setTexture(sf::Texture* tex);





};

#endif
