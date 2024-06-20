#include "Stage.hpp"
#include "StageMgr.hpp"
// GAME STATE BASE

Stage::Stage(StageMgr& l_mgr) 
	: mgr_{ l_mgr }
	, sprites_{}
	//, backgroundTex{}
	//, sfBgSpr{}
{ sprites_.clear(); }
StageMgr& Stage::mgr() { return mgr_; }

// THE GAME STATES





// SANDBOX STATE
//  implementation details in sandbox_state.cpp