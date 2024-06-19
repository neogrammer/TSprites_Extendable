#ifndef ENEMY_HPP__
#define ENEMY_HPP__

#include "Sprite.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>



class Enemy {
public:
    void update(const sf::Time& l_dt) {
        std::cout << "Updating a Enemy Sprite\n";

    }

    void render(sf::RenderWindow& l_wnd) {
        sf::RectangleShape shape(sf::Vector2f(100, 50));
        shape.setFillColor(sf::Color::Red);
        l_wnd.draw(shape);
    }
};

void update(Enemy& player, const sf::Time& deltaTime) {
    player.update(deltaTime);
}

void render(Enemy& player, sf::RenderWindow& window) {
    player.render(window);
}

#endif
