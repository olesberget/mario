#include "QuestionBlock.hpp"
#include "iostream"

QuestionBlock::QuestionBlock(const std::string& textureFile, const std::string& hitTextureFile, const sf::Vector2f& position) : isHit(false), is_Solid(false) {
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Failed to load question block texture.");
    }

    if (!hitTexture.loadFromFile(hitTextureFile)) {
        throw std::runtime_error("Failed to load hit texture for question block.");
    }

    sprite.setTexture(texture);
    sprite.setPosition(position);
    currentFrameIndex = 0;
    frameTime = sf::seconds(0.2f);
    elapsedTime = sf::Time::Zero;

    int blockWidth = texture.getSize().x / 4;  // Width of a single block
    int blockHeight = texture.getSize().y;     // Height of a single block
    blockRect = sf::IntRect(0, 0, blockWidth, blockHeight);

    // Define the animation frames
    for (int i = 0; i < 4; ++i) {
        int frameLeft = i * (texture.getSize().x / 4);
        int frameTop = 0;
        sf::IntRect frameRect(frameLeft, frameTop, texture.getSize().x / 4, texture.getSize().y);
        animationFrames.push_back(frameRect);
    }
}

void QuestionBlock::update(sf::Time deltaTime) {

    elapsedTime += deltaTime;

    if (elapsedTime >= frameTime) {
        elapsedTime -= frameTime;
        currentFrameIndex = (currentFrameIndex + 1) % animationFrames.size();
    }
}

void QuestionBlock::hit() {
    isHit = true;
    is_Solid = true;
    sprite.setTexture(hitTexture);

    // Update the bounding box to fit the size of the single block
    int blockWidth = hitTexture.getSize().x;
    int blockHeight = hitTexture.getSize().y;
    blockRect = sf::IntRect(0, 0, blockWidth, blockHeight);
    sprite.setTextureRect(blockRect);
}

void QuestionBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    sf::Sprite mutableSprite = sprite; // Create a mutable copy of the sprite

    if (isHit) {
        mutableSprite.setTexture(hitTexture);
        mutableSprite.setTextureRect(blockRect);
    } else {
        mutableSprite.setTexture(texture);
        mutableSprite.setTextureRect(animationFrames[currentFrameIndex]);
    }

    target.draw(mutableSprite, states);
}

void QuestionBlock::reset() {
    sprite.setTexture(texture);
    sprite.setTextureRect(animationFrames[0]);
    currentFrameIndex = 0;
    isHit = false;
    is_Solid = false;
}

sf::FloatRect QuestionBlock::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

bool QuestionBlock::isSolid() const {
    return is_Solid;
}