
#ifndef BULLET_HPP__
#define BULLET_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>
class Sprite;

class Bullet {
    float posx = 0.f, posy = 0.f;

public:

    Bullet();
    void update(const sf::Time& l_dt);
    void render(sf::RenderWindow& l_wnd);

    void finalize();
};

void update(Bullet& bullet, const sf::Time& deltaTime);
void render(Bullet& bullet, sf::RenderWindow& window);
#endif

