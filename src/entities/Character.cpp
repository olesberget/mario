#include "Character.hpp"
#include <SFML/Window/Keyboard.hpp> // For keyboard inputs
#include <stdexcept> // For std::runtime_error

Character::Character(const sf::Vector2f& position) : GameObject(), score(0), isJumping(false), facingLeft(false), isBig(false), moveSpeed(100.0f), jumpSpeed(-500.0f), gravity(1000.0f), verticalVelocity(0.0f), isRunning(false), currentFrame(0), frameWidth(16), frameHeight(16), numFrames(3) {
    sprite.setPosition(position);

    // Load the initial texture for the character
    if (!texture.loadFromFile("../resources/images/MarioIdle.png")) {
        throw std::runtime_error("Failed to load character texture.");
    }

    // Load additional textures
    loadTextures();

    // Load sounds
    loadSounds();

    // Set the initial texture
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
}

void Character::loadTextures() {
    // Loading textures for different states
    if (!marioJumpTexture.loadFromFile("../resources/images/MarioJump.png") || !marioRunTexture.loadFromFile("../resources/images/MarioWalk.png") || !bigMarioIdleTexture.loadFromFile("../resources/images/BigMarioIdle.png") || !bigMarioJumpTexture.loadFromFile("../resources/images/BigMarioJump.png") || !bigMarioRunTexture.loadFromFile("../resources/images/BigMarioWalk.png")) {
        throw std::runtime_error("Failed to load one or more character textures.");
    }
}

void Character::loadSounds() {
    // Load sound effects
    if (!jumpSoundBuffer.loadFromFile("../resources/audio/jump.wav") || !coinSoundBuffer.loadFromFile("../resources/audio/coin.wav") || !powerUpSoundBuffer.loadFromFile("../resources/audio/powerUp.wav")) {
        throw std::runtime_error("Failed to load one or more sound effects.");
    }

    jumpSound.setBuffer(jumpSoundBuffer);
    coinSound.setBuffer(coinSoundBuffer);
    powerUpSound.setBuffer(powerUpSoundBuffer);

    // Assuming music is handled elsewhere or by another component
}

void Character::update(sf::Time deltaTime, Map &map, QuestionBlock &questionBlock, std::vector<Coin> &coins, std::vector<Block> &blocks, std::vector<Mushroom> &mushrooms) {
    handleInput();
    handlePhysics(deltaTime);
    handleCollisions(map, questionBlock, coins, blocks, mushrooms);
    updateAnimation(deltaTime);
}

void Character::handleInput() {
    // Basic left and right movement
    isRunning = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.move(-moveSpeed, 0);
        facingLeft = true;
        isRunning = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.move(moveSpeed, 0);
        facingLeft = false;
        isRunning = true;
    }

    // Jumping
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
        isJumping = true;
        verticalVelocity = jumpSpeed;
        jumpSound.play();
    }
}

void Character::handlePhysics(sf::Time deltaTime) {
    // Apply gravity
    verticalVelocity += gravity * deltaTime.asSeconds();
    sprite.move(0, verticalVelocity * deltaTime.asSeconds());

    // Temporary ground check
    if (sprite.getPosition().y > 500) { // Assuming ground level is at y = 500
        isJumping = false;
        verticalVelocity = 0;
        sprite.setPosition(sprite.getPosition().x, 500); // Reset to ground level
    }
}

void Character::handleCollisions(Map &map, QuestionBlock &questionBlock, std::vector<Coin> &coins, std::vector<Block> &blocks, std::vector<Mushroom> &mushrooms) {
    // Example collision with a question block
    if (sprite.getGlobalBounds().intersects(questionBlock.getGlobalBounds()) && !questionBlock.isHit) {
        questionBlock.hit();
        score += 50; // Assume hitting a question block gives 50 points
    }

    // Add collision handling with map, coins, blocks, and mushrooms here
    // Note: Detailed collision logic will depend on your game's specific requirements
}

void Character::updateAnimation(sf::Time deltaTime) {
    // Update animation based on character state
    if (isJumping) {
        sprite.setTexture(marioJumpTexture);
    } else if (isRunning) {
        // Handle running animation by cycling through frames
        // Example: cycle through 3 frames every 0.2 seconds
        if (animationClock.getElapsedTime() >= frameDuration) {
            currentFrame = (currentFrame + 1) % numFrames;
            animationClock.restart();
        }
        sprite.setTexture(marioRunTexture);
        sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
    } else {
        // Idle state
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    }

    // Flip sprite based on facing direction
    sprite.setScale(facingLeft ? -1.f : 1.f, 1.f);
}

int Character::getScore() const {
    return score;
}
