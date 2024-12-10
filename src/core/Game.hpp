#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "../world/Map.hpp"
#include "../entities/Character.hpp"
#include "../entities/QuestionBlock.hpp"
#include "../entities/Coin.hpp"
#include "../entities/Block.hpp"
#include "../entities/Mushroom.hpp"

class Game {
public:
    Game();
    void run();
    void stop();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void updateScore();
    void updateCoins(sf::Time deltaTime);
    void updateBlocks(sf::Time deltaTime);
    void updateMushrooms(sf::Time deltaTime);

    sf::RenderWindow window;
    Map map;
    Character character;
    QuestionBlock questionBlock;
    std::vector<Coin> coins;
    std::vector<Block> blocks;
    sf::Font font;
    sf::Text scoreText;
    int score;
    std::vector<Mushroom> mushrooms;
};

#endif // GAME_HPP
