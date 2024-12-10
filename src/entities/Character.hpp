#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../world/Map.hpp"
#include "QuestionBlock.hpp"
#include "Coin.hpp"
#include "Block.hpp"
#include "Mushroom.hpp"
#include "../utils/GameObject.hpp"

class Character : public GameObject {
public:
    Character(const sf::Vector2f& position, const std::string& textureFile);

    void update(sf::Time deltaTime, Map& map, QuestionBlock& questionBlock, 
                std::vector<Coin>& coins, std::vector<Block>& blocks,
                std::vector<Mushroom>& mushrooms) override;

    int getScore() const;

private:
    void loadTextures();
    void loadSounds();
    void handlePhysics(sf::Time deltaTime, Map& map);
    void handleCollisions(Map& map, QuestionBlock& questionBlock, 
        std::vector<Coin>& coins, std::vector<Block>& blocks, 
        std::vector<Mushroom>& mushrooms);

    // Textures for different character states
    sf::Texture marioJumpTexture;
    sf::Texture marioRunTexture;
    sf::Texture bigMarioIdleTexture;
    sf::Texture bigMarioJumpTexture;
    sf::Texture bigMarioRunTexture;

    // Sounds
    sf::SoundBuffer jumpSoundBuffer;
    sf::Sound jumpSound;
    sf::SoundBuffer coinSoundBuffer;
    sf::Sound coinSound;
    sf::SoundBuffer powerUpSoundBuffer;
    sf::Sound powerUpSound;

    bool isJumping = false;
    bool facingLeft = false;
    bool isBig = false;
    float moveSpeed = 100.0f;
    float jumpSpeed = -500.0f;
    float gravity = 1000.0f;
    float verticalVelocity = 0.0f;
    int score = 0;

    // Animation
    bool isRunning = false;
    sf::Clock animationClock;
    sf::Time frameDuration = sf::seconds(0.2f);
    int currentFrame = 0;
    int frameWidth = 16;
    int frameHeight = 16;
    int numFrames = 3;
};

#endif // CHARACTER_HPP