#ifndef QUESTIONBLOCK_HPP
#define QUESTIONBLOCK_HPP


#include <SFML/Graphics.hpp>
#include <vector>

class QuestionBlock : public sf::Drawable, public sf::Transformable {
public:
    QuestionBlock(const std::string& textureFile, const std::string& hitTextureFile, const sf::Vector2f& position);
    void update(sf::Time deltaTime);
    void hit();
    bool isHit;
    bool isSolid() const;
    void reset();
    sf::FloatRect getGlobalBounds() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Texture texture;
    sf::Texture hitTexture;
    sf::Sprite sprite;
    std::vector<sf::IntRect> animationFrames;
    int currentFrameIndex;
    sf::Time frameTime;
    sf::Time elapsedTime;
    sf::IntRect blockRect;
    bool is_Solid;
};

#endif // QUESTIONBLOCK_HPP