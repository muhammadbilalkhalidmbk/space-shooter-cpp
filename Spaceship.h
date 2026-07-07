#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"

class Spaceship {
private:
    sf::Sprite sprite;
    sf::Texture* texturePtr = nullptr;
    sf::CircleShape leftDrone;
    sf::CircleShape rightDrone;
    sf::Texture* bulletTexturePtr = nullptr;

    float speed;
    bool hasMultiGun = false;
    bool hasDrone = false;

    sf::Clock chargeClock;
    bool isCharging = false;
    bool chargedShotReady = false;


public:
    std::vector<Bullet> bullets;

    Spaceship();
    void moveLeft();
    void moveRight();
    void update();
    void draw(sf::RenderWindow& window);

    void shoot(bool charged = false);

    std::vector<Bullet>& getBullets();
    sf::FloatRect getBounds() const;

    void enableMultiGun(bool enable);
    void enableDrone(bool enable);
    bool isMultiGunEnabled() const;
    bool isDroneEnabled() const;
    void setTexture(sf::Texture* tex);
    
    void setBulletTexture(sf::Texture* tex);


};

#endif
