#ifndef SANDBOXSTATE_HPP__
#define SANDBOXSTATE_HPP__
#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Sprite.hpp"

class GameStateMgr;
// SANDBOX STATE
struct SandboxState : GameState {
public:
    SandboxState(GameStateMgr& l_mgr);
    ~SandboxState() override = default;
    void handleInput() override final;
    void update(const sf::Time& l_dt) override final;
    void render(sf::RenderWindow& l_wnd) override final;
private:
    std::vector<Sprite> sprites_;

};

#endif