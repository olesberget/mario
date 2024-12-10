#include "Map.hpp"
#include <fstream>
#include <streambuf>

Map::Map(const std::string& mapFile, const std::string& tilesetFile) {
    // Load the JSON file and parse it
    std::ifstream mapFileStream(mapFile);
    std::string jsonStr((std::istreambuf_iterator<char>(mapFileStream)), std::istreambuf_iterator<char>());
    mapFileStream.close();

    rapidjson::Document document;
    document.Parse(jsonStr.c_str());

    const rapidjson::Value& layers = document["layers"];
    const int mapWidth = document["width"].GetInt();
    const int mapHeight = document["height"].GetInt();
    const int tileSize = document["tilewidth"].GetInt();

    if (!tilesetTexture.loadFromFile(tilesetFile)) {
        throw std::runtime_error("Failed to load tileset image.");
    }

    // Generate the tiles
    for (const rapidjson::Value& layer : layers.GetArray()) {
        const rapidjson::Value& layerData = layer["data"];
        for (int y = 0; y < mapHeight; ++y) {
            for (int x = 0; x < mapWidth; ++x) {
                int tileIndex = layerData[y * mapWidth + x].GetInt();
                int tilesetColumns = document["tilesets"][0]["columns"].GetInt();
                int tilesetFirstGid = document["tilesets"][0]["firstgid"].GetInt();

                Tile tile;
                tile.sprite.setTexture(tilesetTexture);
                tile.sprite.setTextureRect(sf::IntRect(
                        ((tileIndex - tilesetFirstGid) % tilesetColumns) * tileSize,
                        ((tileIndex - tilesetFirstGid) / tilesetColumns) * tileSize,
                        tileSize,
                        tileSize));
                tile.sprite.setPosition(x * tileSize, y * tileSize);
                tile.index = tileIndex;
                tiles.push_back(tile);
            }
        }
    }
}

const std::vector<Tile>& Map::getTiles() const {
    return tiles;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& tile : tiles) {
        target.draw(tile.sprite, states);
    }
}