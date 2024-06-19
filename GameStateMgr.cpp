#include "GameStateMgr.hpp"
#include "SandboxState.hpp"
#include <memory>

GameStateMgr::GameStateMgr() : states{} 
{
    pushState(std::make_unique<SandboxState>(*this));
}

void GameStateMgr::pushState(std::unique_ptr<GameState> state) {
    states.push(std::move(state));
}
void GameStateMgr::popState() {
    states.pop();
}
GameState* GameStateMgr::getCurrentState() {
    return states.top().get();
}