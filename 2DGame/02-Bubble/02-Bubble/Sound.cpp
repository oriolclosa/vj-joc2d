#include "Sound.h"

void Sound::init(){
	SDL_Init(SDL_INIT_AUDIO);
	soundBack.init();
	musicMenu.load("sounds/menu.wav");
	musicMenuPlaying = false;
	musicLevel.load("sounds/level.wav");
	musicLevelPlaying = false;
	soundPlayer.init();
	musicPlayer[1].load("sounds/player1.wav");
	musicPlayer[2].load("sounds/player2.wav");
	musicPlayer[3].load("sounds/player3.wav");
	musicPlayer[4].load("sounds/player4.wav");
	musicPlayer[5].load("sounds/player5.wav");
	musicPlayer[6].load("sounds/player6.wav");
	musicPlayer[7].load("sounds/player7.wav");
}

void Sound::playMenu() {
	if (!musicMenuPlaying) {
		musicMenuHandle = soundBack.play(musicMenu);
		soundBack.setVolume(musicMenuHandle, 0.5f);
		soundBack.setLooping(musicMenuHandle, 1);
		musicMenuPlaying = true;
	}
}

void Sound::stopMenu() {
	soundBack.stop(musicMenuHandle);
	musicMenuPlaying = false;
}

void Sound::playLevel() {
	if (!musicLevelPlaying) {
		musicLevelHandle = soundBack.play(musicLevel);
		soundBack.setVolume(musicLevelHandle, 0.5f);
		soundBack.setLooping(musicLevelHandle, 1);
		musicLevelPlaying = true;
	}
}

void Sound::stopLevel() {
	soundBack.stop(musicLevelHandle);
	musicLevelPlaying = false;
}

void Sound::playPlayer(int effect) {
	musicPlayerHandle[effect] = soundPlayer.play(musicPlayer[effect]);
	soundPlayer.setVolume(musicPlayerHandle[effect], 2.0f);
}