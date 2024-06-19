#include "SandboxState.hpp"
#include "sprites.hpp"
#include "GameStateMgr.hpp"
#include "util.hpp"
#include <iostream>
// SANDBOX STATE
SandboxState::SandboxState(GameStateMgr& l_mgr) 
	: GameState{ l_mgr }
	, sprites_{}
{
	sprites_.clear();

	sprites_.emplace_back(Player{});
	sprites_.emplace_back(Enemy{});
	sprites_.emplace_back(Bullet{});

}

void SandboxState::handleInput() 
{ 
	return; 
}


void SandboxState::update(const sf::Time& l_dt) 
{ 
	updateAllSprites(sprites_, l_dt);
	return;

}


void SandboxState::render(sf::RenderWindow& l_wnd) 
{ 
	renderAllSprites(sprites_, l_wnd);
	std::cout << " End of one game frame " << std::endl;
	return; 
}
