#include "util.hpp"

void renderAllSprites(const std::vector<Sprite>& sprites, sf::RenderWindow& l_wnd)
{
	for (const auto& sprite : sprites)
	{
		render(sprite, l_wnd);
	}
}

void updateAllSprites(const std::vector<Sprite>& sprites, const sf::Time& l_dt)
{
	for (const auto& sprite : sprites)
	{
		update(sprite, l_dt);
	}
}


