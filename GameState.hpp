#ifndef GAMESTATE_HPP__
#define GAMESTATE_HPP__
#include <SFML/Graphics.hpp>
#include <vector>


class GameStateMgr;


// GAME STATE BASE
class GameState {
protected: GameStateMgr* m_mgr;
public:
        GameState(GameStateMgr& l_mgr);
        virtual ~GameState() = default;
        virtual void handleInput() = 0;
        virtual void update(const sf::Time& deltaTime) = 0;
        virtual void render(sf::RenderWindow& window) = 0;
        GameStateMgr& mgr();
};

#endif

