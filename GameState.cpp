#include "GameState.hpp"
#include "GameStateMgr.hpp"

// GAME STATE BASE

GameState::GameState(GameStateMgr& l_mgr) : m_mgr{ &l_mgr } {}
GameStateMgr& GameState::mgr() { return *m_mgr; }

// THE GAME STATES





// SANDBOX STATE
//  implementation details in sandbox_state.cpp