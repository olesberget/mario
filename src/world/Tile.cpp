#include "Tile.hpp"

Tile::Tile() : index(0) {
    // Default constructor
}

bool Tile::isSolidTile() const {
    std::vector<int> solidTiles = {2068, 2084, 2085, 2088}; // Add other solid tile indices here
    return std::find(solidTiles.begin(), solidTiles.end(), index) != solidTiles.end();
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}
