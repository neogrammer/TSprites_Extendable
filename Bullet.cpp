#include "Bullet.hpp"
#include "Sprite.hpp"

Bullet::Bullet(float l_posx, float l_posy, bool &l_alive, sf::Texture& l_tex, std::string l_direction, float l_bulletSpeed, bool l_friendly)
    : tex{&l_tex}
    , m_direction{ l_direction }
    , m_bulletSpeed{ l_bulletSpeed }
    , m_friendly{ l_friendly }
    , baseIsAlive{l_alive}
{
    
    posx = 40.f;
    posy = 100.f;
    bulletFSM.posx = l_posx;
    bulletFSM.posy = l_posy;
    bulletFSM.vely = 0.f;
    alive = l_alive;
    bulletFSM.velx = (m_direction == "east") ? 400.f : -400.f;
    
}

void Bullet::update(const sf::Time& l_dt) {


    //playerFSM.velx = 0.f;
   // playerFSM.vely = 0.f;

    if (bulletFSM.isType(states_bullet::BulletAlive{}))
    {
        bulletFSM.dt = l_dt.asSeconds();

        animTimer += l_dt;

        if (animTimer.asSeconds() > 0.16f)
        {
            animTimer = sf::Time::Zero;

            if (++currAnimIndex >= 6)
                currAnimIndex = 0;
        }


      

        bulletFSM.posx += bulletFSM.velx * l_dt.asSeconds();

        if (bulletFSM.posx > 800.f)
        {
            dispatch(bulletFSM, OffStageEvent{});
        }
    }
    else if (bulletFSM.isType(states_bullet::BulletCollided{}))
    {
        alive = false;
        baseIsAlive = false;
    }
    else if (bulletFSM.isType(states_bullet::BulletOffStage{}))
    {
        alive = false;
        baseIsAlive = false;

        std::cout << "Marked for death: Bullet" << std::endl;
    }
}

bool Bullet::isAlive()
{
    return baseIsAlive;
}

void Bullet::render(sf::RenderWindow& l_wnd) {

    sf::Sprite tmp;
    tmp.setTexture(*tex);
    tmp.setPosition({ bulletFSM.posx, bulletFSM.posy });
    tmp.setTextureRect(animVec[currAnimIndex]);
    l_wnd.draw(tmp);
}

void Bullet::finalize()
{
}

void update(Bullet& bullet, const sf::Time& deltaTime) {
    bullet.update(deltaTime);
}

bool isAlive(Bullet& bullet)
{
    return bullet.isAlive();
}

void render(Bullet& bullet, sf::RenderWindow& window) {

    bullet.render(window);
}