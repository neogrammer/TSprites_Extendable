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
	bool justShot{ false };
	float shootDelay{ 0.5f };
	sf::Time shootTime{ sf::Time::Zero };
	sf::Texture bulletTex;

	std::vector<sf::Texture> bgTexVec;
	
	void renderBackground(sf::RenderWindow& l_wnd);
	Tilemap tmap;

public:


	float playerPosx = 40.f;
	float playerPosy = 500.f;
	bool playerIsAlive = true;

	float enemyPosx = 500.f;;
	float enemyPosy = 300.f;
	bool enemyIsAlive = true;;

	float bulletPosx = 40.f;
	float bulletPosy = 500.f;
	bool bulletIsAlive = true;

	StageSandbox(StageMgr& l_mgr);

	~StageSandbox() override {}
	void handleInput() override final;
	void update(const sf::Time& l_dt) override final;
	void render(sf::RenderWindow& l_wnd) override final;


};

#endif