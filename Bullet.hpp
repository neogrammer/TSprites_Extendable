
#ifndef BULLET_HPP__
#define BULLET_HPP__

#include "Sprite.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>


class Bullet {
public:
    void update(const sf::Time& l_dt) {
        std::cout << "Updating a Bullet Sprite\n";
    }

    void render(sf::RenderWindow& l_wnd) {
        sf::CircleShape shape(10);
        shape.setFillColor(sf::Color::Yellow);
        l_wnd.draw(shape);
    }
};

void update(Bullet& player, const sf::Time& deltaTime) {
    player.update(deltaTime);
}

void render(Bullet& player, sf::RenderWindow& window) {
    player.render(window);
}

#endif