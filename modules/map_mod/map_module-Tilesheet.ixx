module;
#include <memory>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <iostream>

export module map_mod:Tilesheet;
import :Tile;

export class Tilesheet
{
	// name is the relative path from the assets/textures/tilesheets folder to the texture image file's non-extentioned name, folder included
	//  (e.g.  assets/textures/tilesheets/intro_stage/tileset1.png  would be (m_name = "intro_stage/tileset1")
	std::string m_name{};
	size_t m_pitch{};
	mutable std::vector<Tile> m_tiles{};

public:
	Tilesheet();
	Tilesheet(const std::string& l_name, size_t l_pitch, size_t l_numTiles, size_t l_tileSize, std::set<size_t> const& l_nonSolids);
	~Tilesheet();

	Tile* at(size_t index) const;
};

Tilesheet::Tilesheet()
{
	std::cout << "Default ctor for Tilesheet called!  WHY!!!??" << std::endl;
}

Tilesheet::Tilesheet(const std::string& l_name, size_t l_pitch, size_t l_numTiles, size_t l_tileSize, std::set<size_t> const& l_nonSolids)
	: m_name{l_name}
	, m_pitch{l_pitch}
	, m_tiles{}
{
	m_tiles.clear();

	// last row usually a partial.  take into consideration if l_numTiles < l_pitch (aka.. tilesheet subset within a tilesheet image file)
	size_t numRows = l_numTiles / l_pitch + 1;
	size_t numCols = l_pitch;
	


	m_tiles.reserve(l_numTiles);
	for (size_t y = 0; y < numRows; y++)
	{
		for (size_t x = 0; x < numCols; x++)
		{
			size_t index = y * l_pitch + x;
			if (index >= l_numTiles) // tileset has been loaded completely
			{
				break;
			}
			else
			{
				// index is good load the properties for that indexed tile in the vector
				// check the passed in set of non solid indices in the tilesheet and set those tiles accordingly
				if (l_nonSolids.contains(index))
				{
					m_tiles.emplace_back(x * l_tileSize, y * l_tileSize, l_tileSize, l_tileSize, false);
				}
				else
				{
					m_tiles.emplace_back(x * l_tileSize, y * l_tileSize, l_tileSize, l_tileSize, true);
				}
			}
		}
	}
}

Tilesheet::~Tilesheet()
{

}

Tile* Tilesheet::at(size_t index) const
{
	Tile& t = m_tiles.at(index);
	return &t;
}