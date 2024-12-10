#include "Block.hpp"
#include <stdexcept> // For std::runtime_error

Block::Block(const sf::Vector2f& position) : crushed(false), removed(false), scoreValue(100), timeSinceCrushed(0.0f) {
    if (!texture.loadFromFile("../../resources/images/Bricks.png")) {
        throw std::runtime_error("Failed to load block texture.");
    }

    sprite.setTexture(texture);
    sprite.setPosition(position);

    if (!crushedBlockTexture.loadFromFile("../../resources/images/CrushedBrick.png")) {
        throw std::runtime_error("Failed to load crushed block texture.");
    }
    if (!transparentTexture.loadFromFile("../../resources/images/transparent.png")) {
        throw std::runtime_error("Failed to load crushed block texture.");
    }
}

void Block::update(sf::Time deltaTime) {
    if (crushed) {
        timeSinceCrushed += deltaTime.asSeconds();
        if (timeSinceCrushed <= 0.3) {
            sprite.setTexture(crushedBlockTexture);
        } else{
            sprite.setTexture(transparentTexture);
            removed = true;
        }
    }
}

void Block::crush() {
    crushed = true;
    timeSinceCrushed = 0.0f; // Reset time since crushed
    sprite.setTexture(crushedBlockTexture); // Immediatly set to crushed texture
}

void Block::reset() {
    crushed = false;
    removed = false;
    timeSinceCrushed = 0.0f;
    sprite.setTexture(texture); // Reset to original texture
}

bool Block::isCrushed() const {
    return crushed;
}

int Block::getScoreValue() const {
    return scoreValue;
}