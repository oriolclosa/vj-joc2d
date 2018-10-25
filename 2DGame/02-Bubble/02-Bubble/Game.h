#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"


#define SCREEN_WIDTH 1138
#define SCREEN_HEIGHT 640


// Game is a singleton (a class with a single instance) that represents our whole application


class Game {

public:
	Game() {}
	
	
	static Game &instance() {
		static Game G;
	
		return G;
	}
	
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
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;
	void setRenderScene(int scene);
	int getRenderScene();
	int getSelectedMainButton();
	void changeSelectMainButton(bool plus);

	int getScreenWidth();
	int getScreenHeight();

private:
	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time
	int render_scene;
	int selected_main_button;

};


#endif // _GAME_INCLUDE


