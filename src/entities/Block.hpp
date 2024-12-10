#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "../utils/GameObject.hpp"

class Block : public GameObject {
public:
    Block(const sf::Vector2f& position);

    // Override update method
    void update(sf::Time deltaTime) override;

    bool isCrushed() const;
    void crush();
    void reset();
    int getScoreValue() const;

private:
    sf::Texture crushedBlockTexture;
    sf::Texture transparentTexture;
    float timeSinceCrushed = 0.0f;
    bool crushed = false;
    bool removed = false;
    int scoreValue = 100;
};

#endif // BLOCK_HPP