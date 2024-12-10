#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>

class GameObject : public sf::Drawable, public sf::Transformable {
    public:
        // Constructor
        GameObject();

        // Virtual destructor to ensure proper cleanup of derived classes
        virtual ~GameObject();

        // Update method to be overridden by derived classes
        virtual void update(sf::Time deltaTime) = 0;

        // Get global bounds for collision detection
        sf::FloatRect getGlobalBounds() const;

    protected:
        sf::Sprite sprite;
        sf::Texture texture;

        // Inherited from sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif // GAME_OBJECT_HPP