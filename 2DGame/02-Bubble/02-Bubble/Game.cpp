#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init() {
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init();
	render_scene = 0;
	selected_main_button = 0;
	render_walkable = false;
	global_score = 0;
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
	//printf("%d\n",Game::instance().getRenderScene());
	//printf("%d",key);
	if (key == 27) // Escape code
		bPlay = false;
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
	else if (key == 13) {
		if (getRenderScene() == 1) {
			switch(getSelectedMainButton()) {
				case 0:
					scene.updateLevel(0);
					render_scene = 2;
					break;
				case 1: 
					render_scene = 3;
					break;
				case 2: 
					render_scene = 4;
					break;
				case 3: 
					bPlay = false;
					break;
			}
		}
		else if (getRenderScene() == 3 || getRenderScene() == 4) {
			render_scene = 1;
		}
		else if (getRenderScene() == 5) {
			render_scene = 1;
			global_score = 0;
		}
		render();
	}
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
	if (plus) ++selected_main_button;
	else --selected_main_button;

	if (selected_main_button < 0) selected_main_button = 3;
	else selected_main_button = selected_main_button % 4;
}

Scene Game::getScene() {
	return scene;
}

void Game::setScore(int score) {
	global_score = score;
}

int Game::getScore() {
	return global_score;

}