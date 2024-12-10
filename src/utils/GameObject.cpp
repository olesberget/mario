#include "GameObject.hpp"

GameObject::GameObject() {}

GameObject::~GameObject() {}

sf::FloatRect GameObject::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform(); // Apply the GameObject's transform
    target.draw(sprite, states); // Draw the sprite
}