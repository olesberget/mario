#include "Coin.hpp"
#include <iostream>
#include <stdexcept>

Coin::Coin(const sf::Vector2f& position)
        : GameObject(), currentFrameIndex(0), active(true) {
    if (!texture.loadFromFile("../resources/images/Coin.png")) {
        throw std::runtime_error("Failed to load coin texture.");
    }


    sprite.setTexture(texture);
    sprite.setPosition(position);

    int frameWidth = texture.getSize().x / 10;  // Assuming 10 frames in your animation
    int frameHeight = texture.getSize().y;

    // Set up animation frames
    for (int i = 0; i < 10; ++i) {
        animationFrames.push_back(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
    }

    sprite.setTextureRect(animationFrames[0]); // Set initial frame

    // Assuming the desired size is 50x50 pixels
    float scaleX = 25.0f / frameWidth;
    float scaleY = 25.0f / frameHeight;
    sprite.setScale(scaleX, scaleY);
}

void Coin::update(sf::Time deltaTime) {
    if (!active) {
        return;
    }

    elapsedTime += deltaTime;

    if (elapsedTime >= frameTime) {
        elapsedTime -= frameTime;
        currentFrameIndex = (currentFrameIndex + 1) % animationFrames.size();
        sprite.setTextureRect(animationFrames[currentFrameIndex]);
    }


}

bool Coin::isActive() const {
    return active;
}

void Coin::setActive(bool active) {
    this->active = active;
}

void Coin::reset(){
    active = true;
    currentFrameIndex = 0;
    elapsedTime = sf::Time::Zero;
    sprite.setTextureRect(animationFrames[0]);
}