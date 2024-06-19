#ifndef SPLASHSTATE_HPP__
#define SPLASHSTATE_HPP__
// The Game States
#include "GameState.hpp"
#include <SFML/Graphics.hpp>

class GameStateMgr;
// SPLASH STATE
struct SplashState : GameState {
public:
    SplashState(GameStateMgr& l_mgr);
    ~SplashState() override = default;
    void handleInput() override final;
    void update(const sf::Time& l_dt) override final;
    void render(sf::RenderWindow& l_wnd) override final;
};

#endif