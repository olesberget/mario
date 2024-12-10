#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

class Tile : public sf::Drawable {
public:
    Tile();

    sf::Sprite sprite;
    int index;

    bool isSolidTile() const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // TILE_HPP