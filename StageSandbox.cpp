#include "StageSandbox.hpp"
#include "sprites.hpp"
#include "StageMgr.hpp"
#include "util.hpp"
#include <iostream>

// Intro Stage
StageSandbox::StageSandbox(StageMgr& l_mgr)
	: Stage{ l_mgr }
{

	

	sprites_.emplace_back(Player{});
	sprites_.emplace_back(Enemy{});
	sprites_.emplace_back(Bullet{});

	//backgroundTex.loadFromFile("");
	//sfBgSpr.setTexture(backgroundTex);

	//tilesetTex.loadFromFile("");
	//sfTilesetSpr.setTexture(tilesetTex);

	std::cout << "StageSandbox has been entered" << std::endl;
}

void StageSandbox::handleInput()
{
	return;
}


void StageSandbox::update(const sf::Time& l_dt)
{
	// updateBackgroun();
	// updateTilemap();


	updateAllSprites(sprites_, l_dt);
	return;

	// run collision checks

}


void StageSandbox::render(sf::RenderWindow& l_wnd)
{


	// renderBackground();
	// render tilemap();


	// for all sprites, sprite.finalize().  this is where the underlying sf::Sprite position is updated and the animation is set to the 
	// correct frame after all the updates from itself, and the collision detections, which may have moved it again, so we wait till now 
	// to propagate all the changes to be reflected in what displays on the screen

	// finalizeSprites();
	renderAllSprites(sprites_, l_wnd);
	return;
}
