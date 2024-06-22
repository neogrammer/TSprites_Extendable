#include "util.hpp"
#include <iostream>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"


void renderAllSprites(const std::vector<Sprite>& sprites, sf::RenderWindow& l_wnd)
{
	for (const auto& sprite : sprites)
	{
		render(sprite, l_wnd);
	}
}

std::vector<int> deleteSprites(const std::vector<Sprite>& sprites)
{
	std::vector<int> tmp;
	for (const auto& sprite : sprites)
	{
		int i = 0;
	}
	return tmp;
}

void updateAllSprites(const std::vector<Sprite>& sprites, const sf::Time& l_dt)
{


	for (const auto& sprite : sprites)
	{
		update(sprite, l_dt);

	
	}
}


