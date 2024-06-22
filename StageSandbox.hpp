#ifndef STAGESANDBOX_HPP__
#define STAGESANDBOX_HPP__
#include <vector>
#include "Stage.hpp"
#include <SFML/Graphics/Texture.hpp>
import map_mod;

class StageMgr;
// this is the sandbox stage for right now

class StageSandbox : public Stage
{
	std::vector<sf::Texture> bgTexVec;
	
	void renderBackground(sf::RenderWindow& l_wnd);
	Tilemap tmap;

public:
	StageSandbox(StageMgr& l_mgr);

	~StageSandbox() override {}
	void handleInput() override final;
	void update(const sf::Time& l_dt) override final;
	void render(sf::RenderWindow& l_wnd) override final;
};

#endif