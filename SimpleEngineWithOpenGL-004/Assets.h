#pragma once
#include<map>
#include<string>
#include"Texture.h"
using std::map;
using std::string;

class Assets
{
public:
	static std::map<std::string, Texture> textures;

	//Loads a texture from file
	static Texture loadTexture(Renderer& rendererP, const string& filename, const string& name);

	//Retrieves a strored tetxure
	static Texture& getTexture(const std::string& name);

	//properly de-allocates all loaded ressources
	static void clear();

private: 
	Assets(){}

	//Loades a single texture from file

	static Texture LoadTextureFromFile(Renderer& redererP, const string& filename);
};

