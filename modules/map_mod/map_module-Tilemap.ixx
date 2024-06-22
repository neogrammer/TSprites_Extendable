module;
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <utility>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <set>

export module map_mod:Tilemap;
import :Tile;
import :Tilesheet;

export class Tilemap
{
	std::list<std::unique_ptr<Tilesheet> > m_tilesheet_layers{};
	std::list<std::unique_ptr<sf::Texture> > m_layer_textures{};
	std::list<std::vector<Tile*>  > m_tilemap_layers{};

	size_t m_mapWidth{};
	size_t m_mapHeight{};

public:
	Tilemap();
	explicit Tilemap(const std::string& l_filename);
	~Tilemap();

	void readIn(const std::string& l_filename);
	void render(sf::RenderWindow& l_wnd);
};
Tilemap::Tilemap()
	: m_tilesheet_layers{}
	, m_layer_textures{}
	, m_tilemap_layers{}
	, m_mapWidth{}
	, m_mapHeight{}
{
	std::cout << "Default Tilemap ctor called!" << std::endl;
}

Tilemap::Tilemap(const std::string& l_filename)
	: m_tilesheet_layers{}
	, m_layer_textures{}
	, m_tilemap_layers{}
	, m_mapWidth{}
	, m_mapHeight{}
{
	m_tilesheet_layers.clear();
	m_layer_textures.clear();
	m_tilemap_layers.clear();

	readIn(l_filename);
}

Tilemap::~Tilemap()
{
	// free the memory without deleting it, because tilesheets will be cleared first a
	// as a member would first, but the tiles are on the stack in that class and when the tilemap tile shared pointers goes to be destroyed
	//  free would be called on dangling pointers, so just set em all to nullptr and let the stack scope clean up the data 
    for (auto& l : m_tilemap_layers)
	{ 
		for (auto& t : l)
			t = nullptr;
	}
}

void Tilemap::readIn(const std::string& l_filename)
{
	size_t currLayerIndex = 0;
	std::ifstream iFile;
	iFile.open(l_filename);

	if (!iFile.is_open())
		return;

	int numLayers;

	iFile >> numLayers;

	if (numLayers <= 0 || numLayers > 1)
	{
		std::cout << "invalid number of layers for a tilemap" << std::endl;
		return;
	}
	
	
	for (int layer = 0; layer < numLayers; layer++)
	{

		std::string texName;
		

		
		int pitch, numTiles, tileSize;
		iFile >> texName >> pitch >> numTiles >> tileSize;

		m_layer_textures.emplace_back(std::make_unique<sf::Texture>());
		auto t_front = m_layer_textures.begin();
		std::advance(t_front, layer);
		(*t_front)->loadFromFile("assets/textures/tilesets/" + texName);

		// now iterate through the arbitrary amount of indices for tiles in that sheet that are not solid and add that indices to a set that we will pass to the ctor
		int placeHolder;
		std::set<size_t> nonSolidIndices;
		nonSolidIndices;
		while (true)
		{
			placeHolder = -1;
			iFile >> placeHolder;
			if (placeHolder == -1)
			{
				std::cout << "Error reading in the non-solids for layer " << layer << std::endl;
				break;
			}

			if (placeHolder == 7777777)
			{
				break;
			}

			if (placeHolder >= 0 && placeHolder < 7777777)
			{
				if (nonSolidIndices.contains(static_cast<size_t>(placeHolder)))
				{
					std::cout << "Duplicate non-solid index in the tilemap config file for layer " << layer << std::endl;
					continue;
				}

				nonSolidIndices.insert(static_cast<size_t>(placeHolder));
			}
			else
			{
				continue;
			}
			
		}
		// data filled into variables fit for emplacement into a tilesheet layer, add and repeat until all are loaded
		size_t p{ static_cast<size_t>(pitch) }, n{ static_cast<size_t>(numTiles) }, s{ static_cast<size_t>(tileSize) };
		m_tilesheet_layers.emplace_back(std::make_unique<Tilesheet>(texName, p, n, s, nonSolidIndices));
	}


	// all tilesheets are loaded into memory witihn this tilemap structure now continue reading in the file, which contains a set of indices
	//  relating to a tile in the corresponding layers tilesheet's tile at that index in the file at that index in the tilemap itself.
	// dont read until end of file, read until tilemap is loaded for the number of layers it has only
	int mapWidthInTiles;
	int mapHeightInTiles;

	
	
	for (int layer = 0; layer < numLayers; layer++)
	{
		mapWidthInTiles = 0;
		mapHeightInTiles = 0;
		iFile >> mapWidthInTiles >> mapHeightInTiles;
		m_mapWidth = static_cast<size_t>(mapWidthInTiles);
		m_mapHeight = static_cast<size_t>(mapHeightInTiles);

		size_t numOfMapTiles = static_cast<size_t>(mapWidthInTiles * mapHeightInTiles);

		m_tilemap_layers.push_back(std::vector<Tile*>());
		auto m_front = m_tilemap_layers.begin();
		std::advance(m_front, layer);
		(*m_front).clear();
		(*m_front).reserve(numOfMapTiles);

		for (int y = 0; y < mapHeightInTiles; y++)
		{
			for (int x = 0; x < mapWidthInTiles; x++)
			{
				int tileSheetIndex; 
				iFile >> tileSheetIndex;

				auto sheet_front = m_tilesheet_layers.begin();
				std::advance(sheet_front, layer);

				(*m_front).push_back((*sheet_front).get()->at(static_cast<size_t>(tileSheetIndex)));
			}
		}

	}
	// should be at end of file and all the tilesheet layers should be loaded with tiles from their correct texture
	// and the tilemap layers should contain pointers to those tiles in the tilesheets corresponding to the correct index of that layer. done
}

void Tilemap::render(sf::RenderWindow& l_wnd)
{
	for (int layer = 0; layer < m_tilemap_layers.size(); layer++)
	{
		auto m_front = m_tilemap_layers.begin();
		std::advance(m_front, layer);
		auto& tmap = (*m_front);

		sf::Sprite tmp{};
		auto layerTexSpot = m_layer_textures.begin();
		std::advance(layerTexSpot, layer);
		tmp.setTexture(**layerTexSpot);

		for (int y = 0; y < 15; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				size_t idx = static_cast<size_t>(y) * m_mapWidth + static_cast<size_t>(x);
				if (idx < 0 || idx >= tmap.size())
				{
					break;
				}
				tmp.setTextureRect(sf::IntRect((int)(tmap.at(idx))->texPosX(), (int)(tmap.at(idx))->texPosX(), (int)(tmap.at(idx))->tw(), (int)(tmap.at(idx))->th()));
				tmp.setPosition(float(x * (int)tmap[0]->tw()), float(y * (int)tmap[0]->th()));
				l_wnd.draw(tmp);
			}
		}
	}
}