#ifndef COIN_HPP
#define COIN_HPP

#include "../utils/GameObject.hpp"
#include <vector>

class Coin : public GameObject {
public:
    Coin(const sf::Vector2f& position);

    void update(sf::Time deltaTime) override;
    void setActive(bool active);
    bool isActive() const;
    void reset();

private:
    std::vector<sf::IntRect> animationFrames;
    int currentFrameIndex = 0;
    sf::Time frameTime = sf::seconds(0.1f);
    sf::Time elapsedTime = sf::Time::Zero;
    bool active = true;
};

#endif // COIN_HPP