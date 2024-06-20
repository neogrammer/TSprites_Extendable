#include "Enemy.hpp"
#include "Sprite.hpp"

Enemy::Enemy()
{
    posx = 500.f;
    posy = 200.f;
}

void Enemy::update(const sf::Time& l_dt) {

}

void Enemy::render(sf::RenderWindow& l_wnd) {
    sf::CircleShape shp;
    shp.setRadius(40.f);
    shp.setFillColor(sf::Color::Blue);
    shp.setPosition({ posx,posy });
    l_wnd.draw(shp);
}

void Enemy::finalize()
{
}


void update(Enemy& enemy, const sf::Time& deltaTime) {
    enemy.update(deltaTime);
}

void render(Enemy& enemy, sf::RenderWindow& window) {
    enemy.render(window);
}