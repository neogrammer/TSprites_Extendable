#ifndef PLAYER_HPP__
#define PLAYER_HPP__

#include "Sprite.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

class Player {
public:
    void update(const sf::Time& l_dt) {
        std::cout << "Updating a Player Sprite\n";
    }

    void render(sf::RenderWindow& l_wnd) {
        sf::CircleShape shape(50);
        shape.setFillColor(sf::Color::Green);
        l_wnd.draw(shape);
    }
};

void update(Player& player, const sf::Time& deltaTime) {
    player.update(deltaTime);
}

void render(Player& player, sf::RenderWindow& window) {
    player.render(window);
}
#endif
