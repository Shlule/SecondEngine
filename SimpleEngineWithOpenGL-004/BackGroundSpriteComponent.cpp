#include "BackGroundSpriteComponent.h"
#include"Actor.h"

BackGroundSpriteComponent::BackGroundSpriteComponent(Actor* ownerP, const vector<Texture*>& texturesP, int drawOrderP) :
	SpriteComponent(ownerP, *texturesP[0], drawOrderP),
	scrollSpeed(0.0f),
	screenSize(Vector2(WINDOW_WIDTH, WINDOW_HEIGHT))
{
	setTextures(texturesP);
}
BackGroundSpriteComponent::~BackGroundSpriteComponent()
{
}
void BackGroundSpriteComponent::update(float dt) {
	SpriteComponent::update(dt);
	for (auto& bg : textures) {
		bg.offset.x += scrollSpeed * dt;
		//if this is completly off the sreen, reset offset to
		//the right of the last bg texture
		if (bg.offset.x < -screenSize.x) {
			bg.offset.x = (textures.size() - 1) * screenSize.x - 1;
		}
	}
}
void BackGroundSpriteComponent::draw(Renderer& renderer) {
	//draw each background textures
	for (auto& bg : textures) {
		owner.setPosition(Vector2(bg.offset.x, bg.offset.y));
		renderer.drawSprite(owner, bg.texture, Rectangle::nullRect, Vector2::zero, Renderer::Flip::None);
	}
}
void BackGroundSpriteComponent::setTextures(const vector<Texture*>& texturesP) {
	int count = 0;
	for (auto tex : texturesP) {
		BGTexture temp{ *tex, Vector2(count * screenSize.x,0) };
		textures.emplace_back(temp);
		count++;
	}
}
void BackGroundSpriteComponent::setScrolledSpeed(float scrollSpeedP) {
	scrollSpeed = scrollSpeedP;
}
