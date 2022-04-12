#include "Game.h"
#include"Actor.h"
#include"SpriteComponent.h"
#include"AnimSpriteComponent.h"
#include"Timer.h"
#include"Assets.h"
#include"BackGroundSpriteComponent.h"
#include"Astroid.h"
#include"Ship.h"

bool Game::initialize() {
	bool isWindowIsInit = window.Initialize();
	bool isRendererIsInit = renderer.initialize(window);
	return isWindowIsInit && isRendererIsInit;

}

void Game::loop() {
	Timer timer;
	float dt = 0;
	while (isRunning) {
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}
void Game::close() {
	window.Close();
	renderer.close();
	SDL_Quit();
}
void Game::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	//keyBoard State
	const Uint8* keyBoardState = SDL_GetKeyboardState(nullptr);
	//escape : quit game
	if (keyBoardState[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}
	// actor input
	isUpdatingActors = true;
	for (auto actor : actors) {
		actor->processInput(keyBoardState);
	}
	isUpdatingActors = false;
}
void Game::update(float dt) {
	// update Actors
	isUpdatingActors = true;
	for (auto actor : actors) {
		actor->update(dt);
	}
	isUpdatingActors = false;


	// Move PendingActors to Actors
	//pending actor stack the actor wich was create by an other actor during the update loop
	for (auto pendingActor : pendingActors) {
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	//delete dead Actors
	vector<Actor*> deadActors;
	for (auto actor : actors) {
		if (actor->getState() == Actor::ActorState::Dead) {
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors) {
		delete deadActor;
	}

}

void Game::load() {

	Assets::loadTexture(renderer, "..\\Res\\Res_005-011\\Ship01.png", "Ship01");
	Assets::loadTexture(renderer, "..\\Res\\Res_005-011\\Ship02.png", "Ship02");
	Assets::loadTexture(renderer, "..\\Res\\Res_005-011\\Ship03.png", "Ship03");
	Assets::loadTexture(renderer, "..\\Res\\Res_005-011\\Ship04.png", "Ship04");
	Assets::loadTexture(renderer, "..\\Res\\Res_005-011\\Farback01.png", "Farback01");
	Assets::loadTexture(renderer, "..\\Res\\Res_005-011\\Farback02.png", "Farback02");
	Assets::loadTexture(renderer, "..\\Res\\Res_005-011\\Stars.png", "Stars");
	Assets::loadTexture(renderer, "..\\Res\\Res_005-011\\Astroid.png", "Astroid");
	Assets::loadTexture(renderer, "..\\Res\\Res_005-011\\Ship.png", "Ship");
	
	

	const int astroidNumber = 20;
	for (int i = 0; i < astroidNumber; i++) {
		new Astroid();
	}

	//single Sprite
	/*
	auto actor = new Actor();
	auto sprite = new SpriteComponent(actor, Assets::getTexture("ship01"));
	actor->setPosition(Vector2{ 100,100 });
	*/

	//controlled ship
	Ship* ship01 = new Ship();
	ship01->setPosition(Vector2{ 100,300 });

	//animated Sprite
	vector<Texture*> animTexture{
		&Assets::getTexture("Ship01"),
		&Assets::getTexture("Ship02"),
		&Assets::getTexture("Ship03"),
		&Assets::getTexture("Ship04"),
	};

	Actor* ship = new Actor();
	AnimSpriteComponent* animatedSprite = new AnimSpriteComponent(ship, animTexture);
	ship->setPosition(Vector2{ 100,300 });

	//backGround
	//create the "far back" background
	vector<Texture*> bgTexsFar{
		&Assets::getTexture("Farback01"),
		&Assets::getTexture("Farback02")
	};
	Actor* bgFar = new Actor();
	BackGroundSpriteComponent* bgSpritesFar = new BackGroundSpriteComponent(bgFar, bgTexsFar);
	bgSpritesFar->setScrolledSpeed(-100.0f);

	//create a closer backGround
	Actor* bgClose = new Actor();
	std::vector<Texture*>bgTexsClose{
		&Assets::getTexture("Stars"),
		&Assets::getTexture("Stars")
	};
	BackGroundSpriteComponent* bgSpritesClose = new BackGroundSpriteComponent(bgClose, bgTexsClose, 50);
	bgSpritesClose ->setScrolledSpeed(-200.0f);
}

void Game::unload() {
	//delete actors
	//beacuse ~Actor call Remove Actor , have to use a different loop style
	while (!actors.empty()) {
		delete actors.back();
	}
	//ressources
	Assets::clear();
}
void Game::addActor(Actor* actor) {
	if (isUpdatingActors) {
		pendingActors.emplace_back(actor);
	}
	else {
		actors.emplace_back(actor);
	}
}
void Game::removeActor(Actor* actor) {
	//erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors)) {
		//swap to end of vector and pop offf(avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors)) {
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}
void Game::render() {
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}


