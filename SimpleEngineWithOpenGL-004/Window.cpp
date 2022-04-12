#include "Window.h"
#include"Log.h"

Window::Window(): SDLWindow(nullptr), width(WINDOW_WIDTH),height(WINDOW_HEIGHT)
{}

bool Window::Initialize(){
	int sdlInitResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlInitResult != 0) {
		Log::error(LogCategory::Video, "Unable to initialize SDL");
		return false;
	}
	SDLWindow = SDL_CreateWindow("Wall Pong", 100, 100, width, height, 0);
	if (!SDLWindow) {
		Log::error(LogCategory::System, "Failed toCreate Window");
		return false;
	}
	return true;
}

void Window::Close() {
	SDL_DestroyWindow(SDLWindow);
}
