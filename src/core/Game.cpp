#include <iostream>
#include "Game.hpp"

constexpr int groundLevel = 50;

Game::Game() : window(sf::VideoMode(1600, 320), "Mario Tilemap"),
               map("../resources/tilemaps/finalmap.json", "../resources/images/tilesettest.png"),
               character("../resources/images/MarioIdle.png", 
               "../resources/images/MarioJump.png", 
               "../resources/images/MarioWalk.png", 
               "../resources/images/BigMarioIdle.png", 
               "../resources/images/BigMarioJump.png", 
               "../resources/images/BigMarioWalk.png"),
               questionBlock("../resources/images/questionblock.png", 
               "../resources/images/brunblock.png", 
               sf::Vector2f(200.0f, 225.0f)) {

    if (!font.loadFromFile("../resources/fonts/Scorefont.ttf")) {
        throw std::runtime_error("Failed to load font.");
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(15);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(window.getSize().x - 150, 10);  // Position it at the top right corner
    score = 0;
    scoreText.setString("Score: " + std::to_string(score));
    coins.emplace_back("../resources/images/Coin.png", sf::Vector2f(300.0f, 225.0f));

    sf::Texture mushroomTexture;
    if (!mushroomTexture.loadFromFile("../resources/images/Mushroom.png")) {
        throw std::runtime_error("Failed to load mushroom texture.");
    }

    sf::Vector2f mushroomPosition = sf::Vector2f(820.0f, 288.0f);
    mushrooms.emplace_back(mushroomTexture, mushroomPosition);

    // Create blocks
    blocks.emplace_back(sf::Vector2f(870.0f, 225.0f));
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        }
    }
}

void Game::update(sf::Time deltaTime) {
    character.update(deltaTime, map, questionBlock, coins, blocks, mushrooms);
    updateScore();
    questionBlock.update(deltaTime);
    updateCoins(deltaTime);
    updateBlocks(deltaTime);
    updateMushrooms(deltaTime);
}

void Game::render() {
    window.clear();
    window.draw(map);
    window.draw(character);
    window.draw(questionBlock);
    for (const auto &coin : coins) {
        window.draw(coin);
    }

    for (const auto &block : blocks) {
        window.draw(block);
    }

    for (const auto &mushroom : mushrooms) {
        window.draw(mushroom);
    }

    window.draw(scoreText);
    window.display();
}

void Game::updateScore() {
    score = character.getScore();
    scoreText.setString("Score: " + std::to_string(score));
}

void Game::updateCoins(sf::Time deltaTime) {
    for (auto &coin: coins) {
        coin.update(deltaTime);
    }

    for (auto &coin: coins) {
        if (character.getGlobalBounds().intersects(coin.getGlobalBounds()) && coin.isActive()) {
            coin.setActive(false);
            score += 50;
            updateScore();
        }
    }
}

void Game::updateBlocks(sf::Time deltaTime) {
    for (auto &block: blocks) {
        block.update(deltaTime);
        if (character.getGlobalBounds().intersects(block.getGlobalBounds()) && !block.isCrushed()) {
            block.crush();
            score += block.getScoreValue();
            updateScore();
        }
    }
}

void Game::updateMushrooms(sf::Time deltaTime) {
    for (auto &mushroom: mushrooms) {
        mushroom.update(deltaTime, map);
    }
}
