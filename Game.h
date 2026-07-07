#ifndef GAME_H
#define GAME_H
#include "Spaceship.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Enemy.h"
#include <string>
#include <vector>
#include "Boss.h"
#include "EnemyBullet.h"
#include "BossBullet.h"
#include "PowerUp.h"




class Game {
private:
    sf::RenderWindow window;
    sf::Event event;
    bool isRunning;
    Spaceship spaceship;

    std::vector<Enemy> enemies;
    int score;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    int lives;
    int level;
    bool bossActive;
    bool levelCompleted;
    int enemiesDefeated;
    int playerHealth;
    bool gameWon;
    bool gameOver;

    Boss boss;
    std::vector<EnemyBullet> enemyBullets;
    std::vector<BossBullet> bossBullets;
    sf::Clock bossShootTimer;
    
    std::vector<PowerUp> powerUps;
    sf::Clock powerUpSpawnTimer;
    bool hasMultiGun = false;
    sf::Clock multiGunTimer;
    bool hasDrone = false;
    sf::Clock droneTimer;
    sf::Clock droneFireClock;
    std::map<std::string, sf::Texture> textures;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    sf::Clock spaceHoldClock;
    bool spaceHeld = false;
    sf::SoundBuffer shootBuffer;
    sf::Sound shootSound;

    sf::SoundBuffer explodeBuffer;
    sf::Sound explodeSound;

    sf::SoundBuffer powerupBuffer;
    sf::Sound powerupSound;



public:
    Game();
    void run();
    void processEvents();
    void update();
    void render();
    void showStartScreen();
    void reset();
    void spawnEnemies(int currentLevel);
    void showLevelScreen(int level);

    


};

#endif
