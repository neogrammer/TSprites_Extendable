#ifndef SPRITE_HPP__
#define SPRITE_HPP__
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <functional>
#include <type_traits>

class Sprite
{
	struct SpriteConcept
	{
		virtual ~SpriteConcept() = default;
		virtual void do_update(const sf::Time& l_dt) = 0;
		virtual void do_render(sf::RenderWindow& l_wnd) = 0;
		virtual std::unique_ptr<SpriteConcept> clone() const = 0;
	};

	template <typename SpriteT>
	struct SpriteModel : SpriteConcept
	{


		SpriteModel(SpriteT l_sprite)
			: sprite_{ std::move(l_sprite) }
		{}

		void do_update(const sf::Time& l_dt) override
		{
			update(sprite_, l_dt);
		}

		void do_render(sf::RenderWindow& l_wnd) override
		{
			render(sprite_, l_wnd);
		}

		std::unique_ptr<SpriteConcept> clone() const override
		{
			return std::make_unique<SpriteModel>(*this);
		}

		SpriteT sprite_;
	};

	template<typename SpriteT, typename UpdateStrategy, typename RenderStrategy>
	struct ExtendedSpriteModel : SpriteConcept
	{
		explicit ExtendedSpriteModel(SpriteT l_sprite, UpdateStrategy l_updater, RenderStrategy l_renderer)
			: sprite_{ std::move(l_sprite) }
			, updater_{ std::move(l_updater) }
			, renderer_{std::move(l_renderer) }
		{}

		void do_update(const sf::Time& l_dt) override
		{
			updater_(sprite_, l_dt);
		}

		void do_render(sf::RenderWindow& l_wnd) override
		{
		     renderer_(sprite_, l_wnd);
		}
		
		std::unique_ptr<SpriteConcept> clone() const override
		{
			return std::make_unique<ExtendedSpriteModel>(*this);
		}

		SpriteT sprite_;
		UpdateStrategy updater_;
		RenderStrategy renderer_;
	};

	friend void update(const Sprite& sprite, const sf::Time& l_dt)
	{
		sprite.pimpl->do_update(l_dt);
	}

	friend void render(const Sprite& sprite, sf::RenderWindow& l_wnd)
	{
		sprite.pimpl->do_render(l_wnd);
	}

	std::unique_ptr<SpriteConcept> pimpl;
public:

	template <typename SpriteT>
	Sprite(SpriteT sprite)
		: pimpl{ std::make_unique<SpriteModel<SpriteT>>(std::move(sprite)) }
	{}

	Sprite(const Sprite& o)
		: pimpl{ o.pimpl->clone() }
	{}
	Sprite& operator=(const Sprite& o)
	{
		o.pimpl->clone().swap(pimpl);
		return (*this);
	}

	//Sprite(Sprite&&);  undefined on purpose
	// preventing move from making nullptrs
	// moving essentially makes an independent copy
	Sprite& operator=(Sprite&& o) noexcept
	{
		pimpl.swap(o.pimpl);
		return (*this);
	}
};

#endif