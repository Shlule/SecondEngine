#pragma once
#include"Rectangle.h"
#include"Window.h"
#include<SDL_image.h>
#include"Vector2.h"
#include"Actor.h"
#include<SDL.h>

class Renderer
{
public:
	enum class Flip {
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical=SDL_FLIP_VERTICAL
	};
	Renderer();
	~Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	bool initialize(Window& window);

	void beginDraw();
	void draw();
	void endDraw();

	void drawRect(const Rectangle& rect);
	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void drawSprites();
	void drawSprite(const Actor& actor, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const;



	void close();
	inline SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }

private:
	SDL_Renderer* SDLRenderer = nullptr;
	std::vector<SpriteComponent*>sprites;
};

