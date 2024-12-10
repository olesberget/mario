#ifndef MAP_HPP
#define MAP_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.hpp"
#include "../external/rapidjson/document.h"

class Map : public sf::Drawable {
public:
    Map(const std::string& mapFile, const std::string& tilesetFile);
    const std::vector<Tile>& getTiles() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<Tile> tiles;
    sf::Texture tilesetTexture;  // Add this line
};

#endif // MAP_HPP