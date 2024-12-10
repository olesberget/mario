#include "Mushroom.hpp"

Mushroom::Mushroom(const sf::Texture& texture, const sf::Vector2f& position) {
    if (!mushroomTexture.loadFromFile("../resources/images/Mushroom.png")){
        throw std::runtime_error("Failed to load mushroom texture.");
    }
    sprite.setTexture(mushroomTexture);
    sprite.setPosition(position);
    velocity = sf::Vector2f(100.0f, 0.0f);
    direction = Right;
}

void Mushroom::update(sf::Time deltaTime, const Map& map) {
    float frameSeconds = deltaTime.asSeconds();
    sprite.move(velocity * frameSeconds * (direction == Right ? 1.0f : -1.0f));

    if (checkCollision(map)) {
        direction = (direction == Right ? Left : Right);
    }
}

void Mushroom::reset() {
    sprite.setPosition(820.0f, 288.0f);
    velocity = sf::Vector2f(100.0f, 0.0f);
    direction = Right;
}

sf::FloatRect Mushroom::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

bool Mushroom::checkCollision(const Map& map) {
    for (const auto& tile : map.getTiles()) {
        if (tile.isSolidTile() && tile.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
            return true;
        }
    }
    return false;
}