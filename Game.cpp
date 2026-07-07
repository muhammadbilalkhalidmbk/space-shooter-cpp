#include "Game.h"
#include "EnemyBullet.h"
#include "BossBullet.h"

void Game::showStartScreen() {
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    titleText.setString("SPACE SHOOTER");
    titleText.setPosition(180, 200);

    sf::Text promptText;
    promptText.setFont(font);
    promptText.setCharacterSize(24);
    promptText.setFillColor(sf::Color::White);
    promptText.setString("Press Enter to Start");
    sf::FloatRect bounds = promptText.getLocalBounds();
    promptText.setOrigin(bounds.width / 2, bounds.height / 2);
    promptText.setPosition(400, 300);

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Return) {
                gameOver = false;
                return;
            }

        }

        window.clear(sf::Color::Black);
        window.draw(titleText);
        window.draw(promptText);
        window.display();
    }
}
void Game::showLevelScreen(int level) {
    sf::Text levelText;
    levelText.setFont(font);
    levelText.setCharacterSize(48);
    levelText.setFillColor(sf::Color::White);
    levelText.setString("LEVEL " + std::to_string(level));

    sf::FloatRect bounds = levelText.getLocalBounds();
    levelText.setOrigin(bounds.width / 2, bounds.height / 2);
    levelText.setPosition(400, 300);

    sf::Clock timer;
    while (timer.getElapsedTime().asSeconds() < 2.0f) {
        window.clear(sf::Color::Black);
        window.draw(levelText);
        window.display();
    }
}


Game::Game() {
    backgroundTexture.loadFromFile("D:/Hasnainb project/assets/background.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
    800.f / backgroundTexture.getSize().x,
    600.f / backgroundTexture.getSize().y);
    textures["spaceship"].loadFromFile("D:/Hasnainb project/assets/spaceship.png");
    textures["enemy"].loadFromFile("D:/Hasnainb project/assets/enemy.png");
    textures["boss"].loadFromFile("D:/Hasnainb project/assets/boss.png");
    textures["bullet"].loadFromFile("D:/Hasnainb project/assets/bullet.png");
    textures["enemy_bullet"].loadFromFile("D:/Hasnainb project/assets/enemy_bullet.png");
    textures["boss_bullet"].loadFromFile("D:/Hasnainb project/assets/boss_bullet.png");
    textures["powerup_health"].loadFromFile("D:/Hasnainb project/assets/powerup_health.png");
    textures["powerup_multigun"].loadFromFile("D:/Hasnainb project/assets/powerup_multigun.png");
    textures["powerup_drone"].loadFromFile("D:/Hasnainb project/assets/powerup_drone.png");
    shootBuffer.loadFromFile("assets/shoot.wav");
    shootSound.setBuffer(shootBuffer);

    explodeBuffer.loadFromFile("assets/explode.wav");
    explodeSound.setBuffer(explodeBuffer);

    powerupBuffer.loadFromFile("assets/powerup.wav");
    powerupSound.setBuffer(powerupBuffer);

    spaceship.setTexture(&textures["spaceship"]); 
    spaceship.setBulletTexture(&textures["bullet"]);
    boss.setTexture(&textures["boss"]);
    window.create(sf::VideoMode(800, 600), "Space Shooter Game");
    window.setFramerateLimit(60);
    isRunning = true;
    lives = 3;
    playerHealth = 100;
    level = 1;
    bossActive = false;
    levelCompleted = false;
    enemiesDefeated = 0;
    score = 0;
    gameWon = false;

    font.loadFromFile("gamefont.ttf");

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    scoreText.setString("Score: 0");

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(250, 250);
    

    spawnEnemies(level);
}

void Game::run() {
    showLevelScreen(level);
    while (isRunning && window.isOpen()) {
        processEvents();
        update();
        render();
    }
}


void Game::processEvents() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isRunning = false;
            window.close();
        }
    }
}

void Game::update() {
    static bool canShoot = true;
    if (levelCompleted) {
    level++;
    if (level > 3) {
        gameWon = true;
    } else {
        showLevelScreen(level);  
        spawnEnemies(level);
    }
}


    if (!gameOver && !gameWon) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            spaceship.moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            spaceship.moveRight();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    if (!spaceHeld) {
        spaceHoldClock.restart();
        spaceHeld = true;
    } else if (spaceHoldClock.getElapsedTime().asSeconds() >= 1.0f && canShoot) {
        spaceship.shoot(true);
        shootSound.play(); 
        canShoot = false;
    }
} else {
    if (spaceHeld) {
        if (spaceHoldClock.getElapsedTime().asSeconds() < 1.0f && canShoot) {
           
            spaceship.shoot(false);
            shootSound.play();
        }
        canShoot = true;
        spaceHeld = false;
    }
}


        auto& bullets = spaceship.getBullets();
        for (size_t i = 0; i < bullets.size(); ) {
            bool hit = false;
            for (size_t j = 0; j < enemies.size(); ++j) {
                if (bullets[i].getBounds().intersects(enemies[j].getBounds())) {
                    enemies[j].damage();
                    if (enemies[j].isDead()) {
                        enemies.erase(enemies.begin() + j);
                        explodeSound.play();
                        enemiesDefeated++;
                        if (enemies.empty() && !bossActive) {
                            bossActive = true;
                            boss.spawn(level);
                        }
                    }
                    bullets.erase(bullets.begin() + i);
                    score += 10;
                    scoreText.setString("Score: " + std::to_string(score));
                    hit = true;
                    break;
                }
            }
            if (!hit) {
                bullets[i].update();
                ++i;
            }
        }

        if (boss.isAlive()) {
            boss.update();
            if (bossShootTimer.getElapsedTime().asSeconds() > 2.2f) {
    std::vector<BossBullet> newShots = boss.shoot(level, &textures["boss_bullet"]);
    bossBullets.insert(bossBullets.end(), newShots.begin(), newShots.end());
    bossShootTimer.restart();
}

            for (size_t i = 0; i < bullets.size(); ) {
                if (bullets[i].getBounds().intersects(boss.getBounds())) {
                    boss.damage();
                    bullets.erase(bullets.begin() + i);
                    explodeSound.play();
                    score += 20;
                    scoreText.setString("Score: " + std::to_string(score));
                } else {
                    ++i;
                }
            }
            if (!boss.isAlive()) {
                levelCompleted = true;
            }
        }

        for (Enemy& enemy : enemies) {
            enemy.update();
            if (rand() % 1000 < 2.5) {
                enemyBullets.emplace_back(enemy.getPosition().x + 17.5f, enemy.getPosition().y + 40, &textures["enemy_bullet"]);
            }
        }

        for (size_t i = 0; i < enemyBullets.size(); ) {
            enemyBullets[i].update();
            if (enemyBullets[i].getBounds().intersects(spaceship.getBounds())) {
                playerHealth -= 5;
                enemyBullets.erase(enemyBullets.begin() + i);
                if (playerHealth <= 0) {
                    lives--;
                    playerHealth = 100;
                    if (lives <= 0) gameOver = true;
                }
            } else if (enemyBullets[i].isOffScreen()) {
                enemyBullets.erase(enemyBullets.begin() + i);
            } else {
                ++i;
            }
        }

        for (size_t i = 0; i < bossBullets.size(); ) {
            bossBullets[i].update();
            if (bossBullets[i].getBounds().intersects(spaceship.getBounds())) {
                playerHealth -= 15;
                bossBullets.erase(bossBullets.begin() + i);
                if (playerHealth <= 0) {
                    lives--;
                    playerHealth = 100;
                    if (lives <= 0) gameOver = true;
                }
            } else if (bossBullets[i].isOffScreen()) {
                bossBullets.erase(bossBullets.begin() + i);
            } else {
                ++i;
            }
        }

        bool reverse = false;
        for (Enemy& enemy : enemies) {
            float x = enemy.getBounds().left;
            float w = enemy.getBounds().width;
            if (x <= 0 || (x + w) >= 800) {
                reverse = true;
                break;
            }
        }
        if (reverse) {
            for (Enemy& enemy : enemies) {
                enemy.reverseAndDrop();
            }
        }

        for (Enemy& enemy : enemies) {
            if (enemy.getBounds().intersects(spaceship.getBounds())) {
                lives = 0;
                gameOver = true;
            }
        }

        if (boss.isAlive() && boss.getBounds().intersects(spaceship.getBounds())) {
            lives = 0;
            gameOver = true;
        }

        if (levelCompleted) {
    level++;
    if (level > 3) {
        gameWon = true;
    } else {
        showLevelScreen(level);
        spawnEnemies(level);
        levelCompleted = false;  
    }
}


        spaceship.update();
        if (powerUpSpawnTimer.getElapsedTime().asSeconds() > 10.f) {
        int randX = rand() % 740 + 30;
        int type = rand() % 3;
        PowerUpType powerType = static_cast<PowerUpType>(type);
        sf::Texture* tex = nullptr;

        if (powerType == PowerUpType::Health)
        tex = &textures["powerup_health"];
        else if (powerType == PowerUpType::MultiGun)
        tex = &textures["powerup_multigun"];
        else if (powerType == PowerUpType::Drone)
        tex = &textures["powerup_drone"];

        powerUps.emplace_back(static_cast<float>(randX), -20.f, powerType, tex); 



    powerUpSpawnTimer.restart();
}

for (size_t i = 0; i < powerUps.size(); ) {
    powerUps[i].update();

    if (powerUps[i].getBounds().intersects(spaceship.getBounds())) {
        PowerUpType type = powerUps[i].getType();

       if (type == PowerUpType::Health) {
    playerHealth = std::min(100, playerHealth + 25);
} else if (type == PowerUpType::MultiGun) {
    spaceship.enableMultiGun(true);
    multiGunTimer.restart();
} else if (type == PowerUpType::Drone) {
    spaceship.enableDrone(true);
    droneTimer.restart();  
}
    powerupSound.play();
    powerUps.erase(powerUps.begin() + i);
    } else if (powerUps[i].isOffScreen()) {
        powerUps.erase(powerUps.begin() + i);
    } else {
        ++i;
    }
}

if (spaceship.isMultiGunEnabled() && multiGunTimer.getElapsedTime().asSeconds() > 7.f)
    spaceship.enableMultiGun(false);

if (spaceship.isDroneEnabled() && droneTimer.getElapsedTime().asSeconds() > 7.f)
    spaceship.enableDrone(false);
    if (spaceship.isDroneEnabled() && droneFireClock.getElapsedTime().asSeconds() > 0.5f) {
    float x = spaceship.getBounds().left + spaceship.getBounds().width / 2;
    float y = spaceship.getBounds().top;

    spaceship.getBullets().emplace_back(x - 30, y, &textures["bullet"]);
    spaceship.getBullets().emplace_back(x + 30, y, &textures["bullet"]);

    droneFireClock.restart();
}

    }
}



void Game::render() {
    window.clear();
    window.draw(backgroundSprite);

    spaceship.draw(window);

    sf::RectangleShape healthBarBack(sf::Vector2f(200, 10));
    healthBarBack.setFillColor(sf::Color(100, 100, 100));
    healthBarBack.setPosition(10, 40);
    window.draw(healthBarBack);

    sf::RectangleShape healthBar(sf::Vector2f(playerHealth * 2, 10));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(10, 40);
    window.draw(healthBar);

    auto& bullets = spaceship.getBullets();
    for (auto& p : powerUps)p.draw(window);
    for (Bullet& b : bullets) b.draw(window);
    for (Enemy& enemy : enemies) enemy.draw(window);
    for (auto& b : enemyBullets) b.draw(window);
    for (auto& b : bossBullets) b.draw(window);
    if (boss.isAlive()) {
        boss.draw(window);

        sf::RectangleShape bossBarBack(sf::Vector2f(300, 10));
        bossBarBack.setFillColor(sf::Color(100, 100, 100));
        bossBarBack.setPosition(250, 40);
        window.draw(bossBarBack);

        float currentHealth = static_cast<float>(boss.getHealth());
        float maxHealth = static_cast<float>(boss.getMaxHealth());
        float barWidth = (currentHealth / maxHealth) * 300;
        sf::RectangleShape bossBar(sf::Vector2f(barWidth, 10));
        bossBar.setFillColor(sf::Color::Red);
        bossBar.setPosition(250, 40);
        window.draw(bossBar);
    }

    for (int i = 0; i < lives; ++i) {
        sf::CircleShape life(10);
        life.setFillColor(sf::Color::Red);
        life.setPosition(750 - i * 25, 10);
        window.draw(life);
    }

    window.draw(scoreText);
    if (gameOver) {
    sf::RectangleShape overlay(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(overlay);
    window.draw(gameOverText);

    sf::Text restartText;
    restartText.setFont(font);
    restartText.setCharacterSize(24);
    restartText.setFillColor(sf::Color::White);
    restartText.setString("Press R to Restart");
    sf::FloatRect restartBounds = restartText.getLocalBounds();
    restartText.setOrigin(restartBounds.width / 2, restartBounds.height / 2);
    restartText.setPosition(400, 350);
    window.draw(restartText);

    window.display();

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::R) {
                reset();
                return;
            }
        }
    }
    return;
}

    window.display();
}
void Game::reset() {
    lives = 3;
    score = 0;
    playerHealth = 100;

    spaceship = Spaceship(); 
    spaceship.setTexture(&textures["spaceship"]);
    spaceship.setBulletTexture(&textures["bullet"]);

    enemies.clear();
    enemyBullets.clear();
    bossBullets.clear();
    boss = Boss();
    boss.setTexture(&textures["boss"]);

    spawnEnemies(level);

    scoreText.setString("Score: 0");
    isRunning = true;
    bossActive = false;
    levelCompleted = false;
    enemiesDefeated = 0;
    gameWon = false;
    gameOver = false;

    hasMultiGun = false;
    spaceship.enableMultiGun(false);
    spaceship.enableDrone(false);
    droneTimer.restart();
    multiGunTimer.restart();
}



void Game::spawnEnemies(int currentLevel) {
    enemies.clear();

    int count = 30;
    float speed = 1.0f;
    int hp = 1;

    if (currentLevel == 2) {
        count = 35;
        speed = 1.5f;
        hp = 2;
    } else if (currentLevel == 3) {
        count = 40;
        speed = 2.0f;
        hp = 3;
    }

    for (int i = 0; i < count; ++i) {
        float x = static_cast<float>((i % 10) * 60 + 60);
        float y = static_cast<float>((i / 10) * 60 + 30);
        Enemy enemy(x, y);
        enemy.setTexture(&textures["enemy"]);
        enemy.setSpeed(speed);
        enemy.setHealth(hp);

        enemies.push_back(enemy);
    }

    bossActive = false;
    levelCompleted = false;
    enemiesDefeated = 0;
}
