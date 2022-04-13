#pragma once
#include<map>
#include<string>
#include"Texture.h"
#include"Shader.h"
using std::map;
using std::string;

class Assets
{
public:
	static std::map<std::string, Texture> textures;
	static std::map<std::string, Shader> shaders;

	//loads (and generates) a shader progrom from file loading vertex , fragment(and tesselation control,evaluation,
	//geometry) shader's source code. If tc shaderFile, teShaderfile, gSHaderFile are not mullptr, it also loads
	//tesselation and geometry shaders

	static Shader loadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& tcShaderFile, const std::string& teShaderFile, const std::string& gShaderFile, const std::string& name);

	//Retrieves a Stored shader
	static Shader& getShader(const std::string& name);

	//Loads a texture from file
	static Texture loadTexture(IRenderer& rendererP, const string& filename, const string& name);

	//Retrieves a strored tetxure
	static Texture& getTexture(const std::string& name);

	//properly de-allocates all loaded ressources
	static void clear();

private: 
	Assets(){}

	//Loads and generates a shader from file
	static Shader loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderfile, const std::string& tcShaderFile = "", const std::string& teShaderFile = "", const std::string& gShaderFile = "");

	//Loades a single texture from file

	static Texture LoadTextureFromFile(IRenderer& redererP, const string& filename);
};

