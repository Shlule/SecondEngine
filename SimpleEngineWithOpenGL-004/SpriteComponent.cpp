#include "SpriteComponent.h"
#include"Actor.h"
#include"Game.h"

SpriteComponent::SpriteComponent(Actor* ownerP, Texture& textureP, int drawOrderP) :
	Component(ownerP),
	texture(textureP),
	drawOrder(drawOrderP),
	texWidth(textureP.getWidth()),
	texHeight(textureP.getHeight())
{
	// constructor automaticaly add SpriteComponent to the renderList
	//il demande a l'acteur de le faire'
	owner.getGame().getRenderer().addSprite(this);
}

SpriteComponent::~SpriteComponent() {
	owner.getGame().getRenderer().removeSprite(this);
}

void SpriteComponent::setTexture(const Texture& textureP) {
	texture = textureP;
	texture.updateInfo(texWidth, texHeight);
}

void SpriteComponent::draw(IRenderer& renderer) {
	Vector2 origin{ texWidth / 2.0f,texHeight / 2.f }; // draw from the center point
	renderer.drawSprite(owner, texture, Rectangle::nullRect, origin, IRenderer::Flip::None);
}