#include "SplashState.hpp"
#include "GameStateMgr.hpp"

// SPLASH STATE
SplashState::SplashState(GameStateMgr& l_mgr) : GameState{ l_mgr } {}
void SplashState::handleInput() { return; }
void SplashState::update(const sf::Time& l_dt) { return; }
void SplashState::render(sf::RenderWindow& l_wnd) { return; }