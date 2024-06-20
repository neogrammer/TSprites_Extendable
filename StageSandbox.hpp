#ifndef STAGESANDBOX_HPP__
#define STAGESANDBOX_HPP__

#include "Stage.hpp"
class StageMgr;
// this is the sandbox stage for right now

class StageSandbox : public Stage
{
public:
	StageSandbox(StageMgr& l_mgr);

	~StageSandbox() override {}
	void handleInput() override final;
	void update(const sf::Time& l_dt) override final;
	void render(sf::RenderWindow& l_wnd) override final;
};

#endif