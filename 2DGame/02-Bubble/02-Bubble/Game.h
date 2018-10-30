#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "Scene.h"
#include "Sound.h"

#define SCREEN_WIDTH 682
#define SCREEN_HEIGHT 384

// Game is a singleton (a class with a single instance)
// that represents our whole application

class Game {

public:
	Game() {}
	
	static Game &instance() {
		static Game G;
		return G;
	}
	
	// Basic actions
	void preInit();
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	// Keys management
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	// Get screen dimensions
	int getScreenWidth();
	int getScreenHeight();

	// Scene to render management
	void setRenderScene(int scene);
	int getRenderScene();

	// Main menu button management
	int getSelectedMainButton();
	void changeSelectMainButton(bool plus);

	// Merdes del Closa, is this useless?
	void setWalkable(bool walkable);
	int getWalkable();

	// Is this useless too?
	Scene getScene();

	// Score management for the current playthrough
	int getScore();
	void setScore(int score);

	// End state management for the current playthrough
	bool getEndGameState();
	void setEndGameState(bool state);

	// Character management for the current playthrough
	int getSelectedCharacter();
	void changeCharacterSelected(bool right);

private:
	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that we can have access at any time

	int render_scene;				  // Current scene
	int selected_main_button;		  // Current main menu button selected
	bool render_walkable;			  // ??
	int global_score;				  // Score of the current playthrough
	bool win;						  // The playthrough ends with a win?
	int character;					  // Character of the current playthrough
	Sound sound;					  // Sound to play

};


#endif _GAME_INCLUDE


