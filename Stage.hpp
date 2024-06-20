#ifndef STAGE_HPP__
#define STAGE_HPP__

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Sprite.hpp"
class StageMgr;
class Stage {

protected:

	StageMgr& mgr_;
	std::vector<Sprite> sprites_;

	/*sf::Texture backgroundTex;
	sf::Texture tilesetTex;
	sf::Sprite sfBgSpr;
	sf::Sprite sfTilesetSpr;*/

public:
	
	Stage(StageMgr& l_mgr);
	virtual ~Stage() = default;

	virtual void handleInput() = 0;
	virtual void update(const sf::Time& deltaTime) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	StageMgr& mgr();
};

#endif