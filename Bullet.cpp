#include "Bullet.hpp"
#include "Sprite.hpp"

Bullet::Bullet()
{
    posx = 40.f;
    posy = 100.f;
}

void Bullet::update(const sf::Time& l_dt) {
}

void Bullet::render(sf::RenderWindow& l_wnd) {

    sf::CircleShape shp;
    shp.setRadius(10.f);
    shp.setFillColor(sf::Color::Red);
    shp.setPosition({ posx,posy });
    l_wnd.draw(shp);
}

void Bullet::finalize()
{
}

void update(Bullet& bullet, const sf::Time& deltaTime) {
    bullet.update(deltaTime);
}

void render(Bullet& bullet, sf::RenderWindow& window) {

    bullet.render(window);
}