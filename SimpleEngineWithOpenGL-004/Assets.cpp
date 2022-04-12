#include "Assets.h"
#include"Log.h"
#include<sstream>

std::map<std::string, Texture> Assets::textures;

Texture Assets::loadTexture(Renderer& rendererP, const string& filename, const string& name)
{
	textures[name] = LoadTextureFromFile(rendererP, filename.c_str());
	return textures[name];
}

Texture& Assets::getTexture(const string& name) {
	if (textures.find(name) == end(textures)) {
		std::ostringstream loadError;
		loadError << "texture" << name << "does not exist in assets manager.";
		Log::error(LogCategory::Application, loadError.str());
	}
	return textures[name];
}

void Assets::clear() {
	//(properly delete all texture
	for (auto iter : textures)
		iter.second.unload();
	textures.clear();
}

Texture Assets::LoadTextureFromFile(Renderer& rendererP, const string& filename) {
	Texture texture;
	texture.load(rendererP, filename);
	return texture;
}