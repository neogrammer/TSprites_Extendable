#ifndef ENEMY_HPP__
#define ENEMY_HPP__


#include <iostream>
#include <SFML/Graphics.hpp>

class Sprite;

class Enemy {

public:

    bool& baseIsAlive;
    float posx = 0.f, posy = 0.f;
public:
    Enemy(float l_posx, float l_posy, bool& l_isAlive );
    void update(const sf::Time& l_dt); 
    bool isAlive();
    void render(sf::RenderWindow& l_wnd);

    void finalize();
};

void update(Enemy& enemy, const sf::Time& deltaTime);
bool isAlive(Enemy& enemy);
void render(Enemy& enemy, sf::RenderWindow& window);

#endif
