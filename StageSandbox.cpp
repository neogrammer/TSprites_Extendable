#include "StageSandbox.hpp"
#include "sprites.hpp"
#include "StageMgr.hpp"
#include "util.hpp"
#include <algorithm>
#include <iostream>


// Intro Stage
StageSandbox::StageSandbox(StageMgr& l_mgr)
	: Stage{ l_mgr }
	, bulletTex{}
	, bgTexVec{}
	, tmap("assets/configurations/tilemaps/Tilemap1.dat")
{

	bgTexVec.clear();
	bgTexVec.reserve(5);
	bgTexVec.emplace_back(sf::Texture{});
	bgTexVec.back().loadFromFile("assets/textures/background1/1.png");
	bgTexVec.emplace_back(sf::Texture{});
	bgTexVec.back().loadFromFile("assets/textures/background1/2.png");
	bgTexVec.emplace_back(sf::Texture{});
	bgTexVec.back().loadFromFile("assets/textures/background1/3.png");
	bgTexVec.emplace_back(sf::Texture{});
	bgTexVec.back().loadFromFile("assets/textures/background1/4.png");
	bgTexVec.emplace_back(sf::Texture{});
	bgTexVec.back().loadFromFile("assets/textures/background1/5.png");

	bulletTex.loadFromFile("assets/textures/projectiles/bullets/fire03.png");
	
	
	enemies_.emplace_back(Enemy{});

	//sprites_.push_back(player_);
	//sprites_.push_back(enemies_[0]);
	//sprites_.emplace_back(Player{});
	//sprites_.emplace_back(Enemy{});
	
	//sprites_.emplace_back(Bullet{bulletPosx, bulletPosy, bulletIsAlive, bulletTex });

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



	player_.update(l_dt);


	//updateAllSprites(sprites_, l_dt);

	for (auto& e : enemies_)
	{
		e.update(l_dt);
	}

	std::vector<Bullet>::iterator delMe;
	int size = 0;
	for (auto ptr = bullets_.begin(); ptr != bullets_.end(); ptr++)
	{
		ptr->update(l_dt);

		if (ptr->alive == false)
		{
			size++;
			delMe = ptr;
			
		}
	}
	if (size > 0)
	{
		bullets_.erase(delMe);
		sprites_.clear();
	}
	
	


	if (!justShot) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			justShot = true;
			shootTime = sf::Time::Zero;

			bullets_.emplace_back(Bullet{
				(player_.playerFSM.facingRight) ? player_.playerFSM.posx + 60.f : player_.playerFSM.posx + 13.f,
				player_.playerFSM.posy + 42.f, 
				(player_.playerFSM.facingRight) ? "east" : "west", bulletTex });

		

			dispatch(player_.playerFSM, BeganShootingEvent());
			//sprites_.push_back(bullets_.back());
			

		}
	}

	
	shootTime += l_dt;

	if (shootTime >= sf::seconds(shootDelay))
	{
		justShot = false;
	}
		

	return;

	// run collision checks

}


void StageSandbox::render(sf::RenderWindow& l_wnd)
{




	renderBackground(l_wnd);
	
	player_.render(l_wnd);
	

	for (auto& e : enemies_)
	{
		e.render(l_wnd);
	}
	for (auto& b : bullets_)
	{
		
		b.render(l_wnd);
	}
	// render tilemap();
	tmap.render(l_wnd);


	// for all sprites, sprite.finalize().  this is where the underlying sf::Sprite position is updated and the animation is set to the 
	// correct frame after all the updates from itself, and the collision detections, which may have moved it again, so we wait till now 
	// to propagate all the changes to be reflected in what displays on the screen

	// finalizeSprites();
	//renderAllSprites(sprites_, l_wnd);
	return;
}


void StageSandbox::renderBackground(sf::RenderWindow& l_wnd)
{
	sf::Sprite bgLayer1;
	bgLayer1.setTexture(bgTexVec[0]);
	bgLayer1.setPosition({ 0.f, 0.f });
	sf::Sprite bgLayer2;
	bgLayer2.setTexture(bgTexVec[1]);
	bgLayer2.setPosition({ 0.f, 0.f });


	l_wnd.draw(bgLayer1);
	l_wnd.draw(bgLayer2);

	
}