#ifndef _SOUND_INCLUDE
#define _SOUND_INCLUDE


#include <SDL.h>
#include "soloud.h"
#include "soloud_wav.h"


// Sound contains all the music and sounds of our game.
// It is responsible for playing them.

class Sound{

public:
	Sound() {}

	static Sound &instance() {
		static Sound S;
		return S;
	}

	void init();

	void playMenu();
	void stopMenu();

	void playLevel();
	void stopLevel();

	void playPlayer(int effect);


private:
	SoLoud::Soloud soundBack;
	SoLoud::Wav musicMenu;
	bool musicMenuPlaying;
	int musicMenuHandle;
	SoLoud::Wav musicLevel;
	bool musicLevelPlaying;
	int musicLevelHandle;

	SoLoud::Soloud soundPlayer;
	SoLoud::Wav musicPlayer[8];
	int musicPlayerHandle[8];
};

#endif _SOUND_INCLUDE