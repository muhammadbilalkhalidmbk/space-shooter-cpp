#pragma once
#include <SFML/Graphics.hpp>

enum class PowerUpType { Health, MultiGun, Drone };

class PowerUp {
private:
    sf::Sprite sprite;
    sf::Texture* texturePtr = nullptr;
    PowerUpType type;
    float speed;

public:
    PowerUp(float x, float y, PowerUpType t, sf::Texture* tex);
    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    PowerUpType getType() const;
    bool isOffScreen() const;
};
