#pragma once
#include"SpriteComponent.h"
#include<vector>
using std::vector;


class BackGroundSpriteComponent : public SpriteComponent
{
public:
	BackGroundSpriteComponent(Actor* ownerP, const vector<Texture*>& textureP, int draworderP = 10);
	virtual~BackGroundSpriteComponent();
	BackGroundSpriteComponent() = delete;
	BackGroundSpriteComponent(const BackGroundSpriteComponent&) = delete;
	BackGroundSpriteComponent& operator=(const BackGroundSpriteComponent&) = delete;

	float getScrollSpeed() const { return scrollSpeed; }
	void setTextures(const vector<Texture*>& textures);
	void setScreenSize(const Vector2& screenSizeP);
	void setScrolledSpeed(float scrollSpeedP);

	void update(float dt)override;
	void draw(Renderer& renderer)override;

private:
	struct BGTexture {
		BGTexture(Texture& t, Vector2 o): texture(t), offset(o){}
		Texture& texture;
		Vector2 offset;
	};
	std::vector<BGTexture> textures;
	Vector2 screenSize;
	float scrollSpeed;

};

