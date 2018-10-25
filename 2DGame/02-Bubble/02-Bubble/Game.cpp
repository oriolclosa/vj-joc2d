#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init() {
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init();
	render_scene = 0;
	selected_main_button = 1;
	render_walkable = false;
}

bool Game::update(int deltaTime) {
	scene.update(deltaTime);
	
	return bPlay;
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
}

void Game::keyPressed(int key) {
	printf("%d",Game::instance().getRenderScene());
	printf("%d",key);
	if (key == 27) // Escape code
		bPlay = false;
	else if (key >= 48 && key <= 50) {
		render_scene = key - 48;
		scene.render();
	}
	else if (key == 102 && Game::instance().getRenderScene() == 0) {
		render_scene = 1;
		scene.render();
	}
	else if (key == 119 && Game::instance().getRenderScene() == 1) {
		changeSelectMainButton(false);
		render();
	}
	else if (key == 115 && Game::instance().getRenderScene() == 1) {
		changeSelectMainButton(true);
		render();
	}
	else if (key == 112) //p
		render_walkable = !render_walkable;
	else if (key == 110) //n
		scene.setCameraMovement(scene.getCameraMovement() - 10.0f);
	else if (key == 109) //m
		scene.setCameraMovement(scene.getCameraMovement() + 10.0f);
	keys[key] = true;
}

void Game::keyReleased(int key) {
	keys[key] = false;
}

void Game::specialKeyPressed(int key) {
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key) {
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y) {
}

void Game::mousePress(int button) {
}

void Game::mouseRelease(int button) {
}

bool Game::getKey(int key) const {
	return keys[key];
}

bool Game::getSpecialKey(int key) const {
	return specialKeys[key];
}

void Game::setRenderScene(int scene) {
	render_scene = scene;
}

int Game::getRenderScene() {
	return render_scene;
}

void Game::setWalkable(bool walkable) {
	render_walkable = walkable;
}

int Game::getWalkable() {
	return render_walkable;
}

int Game::getScreenWidth() {
	return SCREEN_WIDTH;
}

int Game::getScreenHeight() {
	return SCREEN_HEIGHT;
}

int Game::getSelectedMainButton() {
	return selected_main_button;
}

void Game::changeSelectMainButton(bool plus) {
	if (plus && selected_main_button + 1 < 5) {
		++selected_main_button;
	}
	if (!plus && selected_main_button - 1 > 0) {
		--selected_main_button;
	}
}