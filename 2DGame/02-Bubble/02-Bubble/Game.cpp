#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::preInit() {
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.preInit();
}


void Game::init() {
	scene.init();
	render_scene = 0;
	selected_main_button = 0;
	render_walkable = false;
	global_score = 0;
	win = false;
	character = 0;
	currentLevel = -1;
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
	switch(render_scene) {
		case 0: if (key == 102 || key == 70) { // f F
					render_scene = 1;
					render();
				}
				else if (key == 27) { // Esc
					bPlay = false;
				}
				break;
		case 1: if (key == 27) { // Esc
					render_scene = 0;
					render();
				}
				else if (key == 119 || key == 87) { // w W
					changeSelectMainButton(false);
					render();
				}
				else if (key == 115 || key == 83) { // s S
					changeSelectMainButton(true);
					render();
				}
				else if (key == 32 || key == 13) { // SPACE ENTER
					switch(selected_main_button) {
						case 0:
							character = 0;
							render_scene = 6;
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
					render();
				}
				break;
		case 2: if (key == 27) { // Esc
					scene.updateLevel(-1);
					render_scene = 1;
					render();
				}
				else if (key == 112) //p
					render_walkable = !render_walkable;
				else if (key == 110) //n
					scene.setCameraMovement(scene.getCameraMovement() - 10.0f);
				else if (key == 109) //m
					scene.setCameraMovement(scene.getCameraMovement() + 10.0f);
				break;
		case 3: if (key == 32 || key == 13 || key == 27) { // SPACE ENTER Esc
					render_scene = 1;
					render();
				}
				break;
		case 4: if (key == 32 || key == 13 || key == 27) { // SPACE ENTER Esc
					render_scene = 1;
					render();
				}
				break;
		case 5: if (key == 32 || key == 13) { // SPACE ENTER
					render_scene = 1;
					render();
				}
				break;
		case 6: if (key == 97 || key == 65) { //a A
					changeCharacterSelected(false);
					render();
				}
				else if (key == 100 || key == 68) { // d D
					changeCharacterSelected(true);
					render();
				}
				else if (key == 32 || key == 13) { // SPACE ENTER
					win = false;
					global_score = 0;
					currentLevel = 0;
					scene.updateLevel(0);
					render_scene = 2;
					render();
				}
				else if (key == 27) { // Esc
					render_scene = 1;
					render();
				}
				break;
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

bool Game::getEndGameState() {
	return win;
}

void Game::setEndGameState(bool state) {
	win = state;
}

int Game::getSelectedCharacter() {
	return character;
}

void Game::changeCharacterSelected(bool right) {
	if (right)
		character = (character + 1) % 3;
	else {
		--character;
		if (character < 0) character = 2;
	}
}

int Game:: getCurrentLevel() {
	return currentLevel;
}

void Game::setCurrentLevel(int level) {
	currentLevel = level;
}