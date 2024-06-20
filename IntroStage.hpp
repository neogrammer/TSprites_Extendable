#ifndef INTROSTAGE_HPP__
#define INTROSTAGE_HPP__

#include "Stage.hpp"
class StageMgr;
// this is the sandbox stage for right now

class IntroStage : public Stage
{
public:
	IntroStage(StageMgr& l_mgr);

	~IntroStage() override {}
	void handleInput() override final;
	void update(const sf::Time& l_dt) override final;
	void render(sf::RenderWindow& l_wnd) override final;
};

#endif