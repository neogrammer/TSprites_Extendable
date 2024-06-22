
#ifndef BULLET_HPP__
#define BULLET_HPP__

#include <iostream>
#include <vector>
#include <variant>
#include "Events.hpp"
#include "FSM.hpp"
#include <SFML/Graphics.hpp>
namespace states_bullet {
    struct BulletAlive {};
    struct BulletCollided {};
    struct BulletOffStage {};
}
using BulletStateVar = std::variant<states_bullet::BulletAlive, states_bullet::BulletCollided, states_bullet::BulletOffStage>;

struct BulletTransitions
{


    std::optional<BulletStateVar> operator()(states_bullet::BulletAlive&, const CollidedEvent& e)
    {
        return states_bullet::BulletCollided{ };
    }

    std::optional<BulletStateVar> operator()(states_bullet::BulletAlive&, const OffStageEvent& e)
    {
        return states_bullet::BulletOffStage{ };
    }

    // default
    template<typename State, typename Event>
    std::optional<BulletStateVar> operator()(State&, const Event&) const
    {
        return std::nullopt;
    }

};





class Sprite;
using Bullet_FSM = FSM<BulletStateVar, EventVar, BulletTransitions>;

class Bullet {
public:
    sf::Texture* tex{nullptr};
    float posx = 0.f, posy = 0.f;
    size_t currAnimIndex = 0U;
    sf::Time animTimer{ sf::Time::Zero };
    bool alive{ true };
    std::string m_direction;
    float m_bulletSpeed;
    bool m_friendly;
    bool& baseIsAlive;
public:
    std::vector<sf::IntRect> animVec = {
           {{0 * 14,0},{14,14}},
           {{1 * 14,0},{14,14}},
           {{2 * 14,0},{14,14}},
           {{3 * 14,0},{14,14}},
           {{4 * 14,0},{14,14}},
           {{5 * 14,0},{14,14}}
    };

public:

 


    Bullet(float l_posx, float l_posy, bool& l_isAlive, sf::Texture& l_tex, std::string l_direction = "east", float l_bulletSpeed = 40.f, bool l_friendly = true);

    Bullet_FSM bulletFSM;

    void update(const sf::Time& l_dt);
    bool isAlive();
    void render(sf::RenderWindow& l_wnd);

    void finalize();
};

void update(Bullet& bullet, const sf::Time& deltaTime);
bool isAlive(Bullet& bullet);
void render(Bullet& bullet, sf::RenderWindow& window);
#endif

