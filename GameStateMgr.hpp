#ifndef GAMESTATEMGR_HPP__
#define GAMESTATEMGR_HPP__
#include <stack>
#include <memory>
class GameState;

class GameStateMgr {
    std::stack<std::unique_ptr<GameState>> states;
public:
    GameStateMgr();
    ~GameStateMgr() = default;

    void pushState(std::unique_ptr<GameState> state);
    void popState();
    GameState* getCurrentState();
};

#endif