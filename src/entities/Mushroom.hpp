#ifndef MUSHROOM_HPP
#define MUSHROOM_HPP


#include <SFML/Graphics.hpp>
#include "../world/Map.hpp"

enum Direction { Right, Left };

class Mushroom : public sf::Drawable {
public:
    Mushroom(const sf::Texture& texture, const sf::Vector2f& position);
    void update(sf::Time deltaTime, const Map& map);
    void reset();
    sf::FloatRect getGlobalBounds() const;

    // Added draw function
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite, states);
    }

private:
    bool checkCollision(const Map& map);
    sf::Sprite sprite;
    sf::Texture mushroomTexture;
    sf::Vector2f velocity;
    Direction direction;
};

#endif // MUSHROOM_HPP