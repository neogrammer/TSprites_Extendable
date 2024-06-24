#ifndef STAGE_HPP__
#define STAGE_HPP__

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Sprite.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
class StageMgr;
class Stage {

protected:

	StageMgr& mgr_;
	Player player_;
	std::vector<Sprite> sprites_;
	std::vector<Enemy> enemies_;
	std::vector<Bullet> bullets_;

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