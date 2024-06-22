#ifndef UTIL_HPP__
#define UTIL_HPP__
#include <vector>
#include "Sprite.hpp"

void renderAllSprites(const std::vector<Sprite>& sprites, sf::RenderWindow& l_wnd);
std::vector<int> deleteSprites(const std::vector<Sprite>& sprites);
void updateAllSprites(const std::vector<Sprite>& sprites, const sf::Time& l_dt);

#endif