#include "SandboxState.hpp"
#include "GameStateMgr.hpp"
#include "IntroStage.hpp"
#include "StageMgr.hpp"
#include "Stage.hpp"
#include "util.hpp"
#include <iostream>
#include <memory>
#include <utility>
// SANDBOX STATE
SandboxState::SandboxState(GameStateMgr& l_mgr) 
	: GameState{ l_mgr }
	, stageMgr_{}
{
	stageMgr_ = std::make_unique<StageMgr>();
}

void SandboxState::handleInput() 
{ 
	stageMgr_->getCurrentStage()->handleInput();
	return; 
}


void SandboxState::update(const sf::Time& l_dt) 
{ 
	stageMgr_->getCurrentStage()->update(l_dt);
	return;
}


void SandboxState::render(sf::RenderWindow& l_wnd) 
{ 
	stageMgr_->getCurrentStage()->render(l_wnd);
	return; 
}
