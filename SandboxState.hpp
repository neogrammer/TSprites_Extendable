#ifndef SANDBOXSTATE_HPP__
#define SANDBOXSTATE_HPP__
#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
class Stage;

class StageMgr;
class GameStateMgr;
// SANDBOX STATE


// this is beng set up for a verbatim almost copy as the PlayState, containing the StageMgr
struct SandboxState : GameState {
public:
    SandboxState(GameStateMgr& l_mgr);
    ~SandboxState() override = default;
    void handleInput() override final;
    void update(const sf::Time& l_dt) override final;
    void render(sf::RenderWindow& l_wnd) override final;
private:
    std::unique_ptr<StageMgr> stageMgr_;
};

#endif