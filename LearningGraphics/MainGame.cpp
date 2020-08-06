#include "MainGame.h"
#include "Errors.h"

#include <iostream>
#include <string>
#include <GL/glew.h>

MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 500;
	_screenHeight = 300;
	GameState _gameState = GameState::PLAY;
}

MainGame::~MainGame()
{
	//dtor
}

void MainGame::run()
{
	initSystems();
	_sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);

	gameLoop();
}

void MainGame::initSystems()
{
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		_screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr) {
		fatal_error("SDL Window could not be created!");
	}

	// set up OpenGL context
	SDL_GLContext gl_context = SDL_GL_CreateContext(_window);
	if (gl_context == nullptr) {
		fatal_error("SDL_GL context could not be created!");
	}

	// set up glew
	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatal_error("Could not initialize glew!");
	}

	// to have 2 windows
	// one for drawing, and other one being cleared; and vice versa
	// this keeps things from flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// set the background colour
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	initShaders();

}

void MainGame::initShaders() {
	_colorProgram.compileShaders("../shaders/colorShading.vert.txt", "../shaders/colorShading.frag.txt");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT) {
		processInput();
		drawGame();
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		}
	}
}

void MainGame::drawGame() {
	// set the base depth to 1.0
	glClearDepth(1.0);
	// clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	_sprite.draw(); // draw the sprite
	_colorProgram.unuse();

	// swap the buffer and draw everything to the screen
	SDL_GL_SwapWindow(_window);
}