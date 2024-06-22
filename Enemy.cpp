#include "Enemy.hpp"
#include "Sprite.hpp"

Enemy::Enemy(float l_posx, float l_posy, bool& l_isAlive)
    : baseIsAlive{ l_isAlive }
{
    posx = l_posy;
    posy = l_posx;
}

void Enemy::update(const sf::Time& l_dt) {

}

bool Enemy::isAlive()
{
    return baseIsAlive;
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

bool isAlive(Enemy& enemy)
{
    return enemy.isAlive();
}

void render(Enemy& enemy, sf::RenderWindow& window) {
    enemy.render(window);
}