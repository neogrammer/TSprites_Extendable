#ifndef ENEMY_HPP__
#define ENEMY_HPP__


#include <iostream>
#include <SFML/Graphics.hpp>

class Sprite;

class Enemy {
    float posx = 0.f, posy = 0.f;
public:
    Enemy();
    void update(const sf::Time& l_dt); 

    void render(sf::RenderWindow& l_wnd);

    void finalize();
};

void update(Enemy& player, const sf::Time& deltaTime);

void render(Enemy& player, sf::RenderWindow& window);

#endif
