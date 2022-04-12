#include "RendererOGL.h"
#include<GL/glew.h>
#include"Rectangle.h"
#include"Vector2.h"
#include"Log.h"
#include"SpriteComponent.h"

#include<SDL_image.h>

RendererOGL::RendererOGL(): window(nullptr), vertexArray(nullptr),context(nullptr){}

RendererOGL::~RendererOGL() {}

bool RendererOGL::initialize(Window& windowP) {
	window = &windowP;

	//set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//request a color buffer with 8 byte per rgba channel;
}
