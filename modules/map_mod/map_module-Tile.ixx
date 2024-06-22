module;
#include <iostream>
#include <utility>
#include <memory>

export module map_mod:Tile;

export class Tile
{
	const size_t m_texPosX{ 0 };
	const size_t m_texPosY{ 0 };
	const size_t m_width{0};
	const size_t m_height{0};


	bool m_solid{ true };
public:
	Tile();
	~Tile();
	explicit Tile(size_t l_tw, size_t l_th);
	Tile(size_t l_texPosX, size_t l_texPosY, size_t l_tw, size_t l_th, bool l_solid = true);

	Tile(const Tile& rhs);
	Tile& operator=(const Tile& rhs);
	Tile(Tile&& rhs) noexcept;
	Tile& operator=(Tile&& rhs) noexcept;

	bool isSolid() const;
	size_t texPosX() const;
	size_t texPosY() const;
	size_t tw() const;
	size_t th() const;

	void setSolid(bool l_solid);
};



Tile::Tile() 
{ 
	std::cout << "Default Tile constructor was called.  Investigate further probably" << std::endl; 
};

Tile::~Tile()
{
}

Tile::Tile(size_t l_tw, size_t l_th)
	: m_texPosX{ 0 }
	, m_texPosY{ 0 }
	, m_width{ l_tw }
	, m_height{ l_th }
	, m_solid{ true }
{}

Tile::Tile(size_t l_texPosX, size_t l_texPosY, size_t l_tw, size_t l_th, bool l_solid)
	: m_texPosX{ l_texPosX }
	, m_texPosY{ l_texPosY }
	, m_width{ l_tw }
	, m_height{ l_th }
	, m_solid{ l_solid }
{}

Tile::Tile(const Tile & rhs)
	: m_texPosX{ rhs.m_texPosX }
	, m_texPosY{ rhs.m_texPosY }
	, m_width{ rhs.m_width }
	, m_height{ rhs.m_height }
	, m_solid{ rhs.m_solid }
{}

Tile& Tile::operator=(const Tile& rhs)
{
	*const_cast<size_t*>(&this->m_texPosX) = rhs.m_texPosX;
	*const_cast<size_t*>(&this->m_texPosY) = rhs.m_texPosY;
	*const_cast<size_t*>(&this->m_width) = rhs.m_width;
	*const_cast<size_t*>(&this->m_height) = rhs.m_height;

	this->m_solid = rhs.m_solid;

	return *this;
}

Tile::Tile(Tile&& rhs) noexcept
	: m_texPosX{ std::move(rhs.m_texPosX) }
	, m_texPosY{ std::move(rhs.m_texPosY) }
	, m_width{ std::move(rhs.m_width) }
	, m_height{ std::move(rhs.m_height) }
	, m_solid{ std::move(rhs.m_solid) }
{}

Tile& Tile::operator=(Tile&& rhs) noexcept
{

	*const_cast<size_t*>(&this->m_texPosX) = std::move(rhs.m_texPosX);
	*const_cast<size_t*>(&this->m_texPosY) = std::move(rhs.m_texPosY);
	*const_cast<size_t*>(&this->m_width) = std::move(rhs.m_width);
	*const_cast<size_t*>(&this->m_height) =std::move(rhs.m_height);
	this->m_solid = std::move(rhs.m_solid);
	
	return *this;
}

bool Tile::isSolid() const
{
	return m_solid;
}

size_t Tile::texPosX() const
{
	return m_texPosX;
}

size_t Tile::texPosY() const
{
	return m_texPosY;
}

size_t Tile::tw() const
{
	return m_width;
}

size_t Tile::th() const
{
	return m_height;
}

void Tile::setSolid(bool l_solid)
{
	m_solid = l_solid;
}
