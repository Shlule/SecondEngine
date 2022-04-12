#include "Renderer.h"
#include"Log.h"
#include"Texture.h"
#include"Math.h"
#include"SpriteComponent.h"

Renderer::Renderer() : SDLRenderer(nullptr) {

}
Renderer::~Renderer()
{
}
bool Renderer::initialize(Window& window) {
	SDLRenderer = SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!SDLRenderer) {
		Log::error(LogCategory::Video, "Failed to create renderer");
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		Log::error(LogCategory::Video, "Unable to initialize SDL_Image");
		return false;
	}
	return true;
}

void Renderer::beginDraw() {
	SDL_SetRenderDrawColor(SDLRenderer, 120, 120, 255, 255);
	SDL_RenderClear(SDLRenderer);
}

void Renderer::draw() {
	drawSprites();
}

void Renderer::endDraw() {
	SDL_RenderPresent(SDLRenderer);
}

void Renderer::drawRect(const Rectangle& rect) {
	SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 255, 255);
	SDL_Rect SDLRect = rect.toSDLRect();
	SDL_RenderFillRect(SDLRenderer, &SDLRect);
}

void Renderer::drawSprites() {
	for (auto sprite : sprites) {
		sprite->draw(*this);
	}
}

void Renderer::drawSprite(const Actor& actor, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip)const
{
	SDL_Rect dstRect;// destination rectangle wher i draw in my sreen.

	//because sprite is component of an actor we take his scale position and rotation
	Vector2 position = actor.getPosition();
	float rotation = actor.getRotation();
	float scale = actor.getScale();
	// scale the wdth/height by owner's scale
	dstRect.w = static_cast<int>(tex.getWidth() * scale);
	dstRect.h = static_cast<int>(tex.getHeight() * scale);
	//Center the rectangle around the actor position
	dstRect.x = static_cast<int>(position.x - origin.x);
	dstRect.y = static_cast<int>(position.y - origin.y);

	SDL_Rect* srcSDL = nullptr;
	if (srcRect != Rectangle::nullRect) {
		srcSDL = new SDL_Rect{
			Maths::round(srcRect.x),
			Maths::round(srcRect.y),
			Maths::round(srcRect.width),
			Maths::round(srcRect.height)
		};
	}
	SDL_RenderCopyEx(SDLRenderer, tex.toSDLTexture(), srcSDL, &dstRect, -Maths::toDregrees(rotation), nullptr, SDL_FLIP_NONE);
	delete srcSDL;
}

void Renderer::addSprite(SpriteComponent* sprite) {

	//insert the sprite at the right place in function of draw order
	int spriteDrawOrder = sprite->getDrawOrder();
	auto iter = begin(sprites);
	for (; iter < end(sprites); iter++) {
		if (spriteDrawOrder < (*iter)->getDrawOrder())break;
	}
	sprites.insert(iter, sprite);
}

void Renderer::removeSprite(SpriteComponent* sprite) {
	auto iter = std::find(begin(sprites), end(sprites), sprite);
		sprites.erase(iter);
}
void Renderer::close() {
	SDL_DestroyRenderer(SDLRenderer);
}