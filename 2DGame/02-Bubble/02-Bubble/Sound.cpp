#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include "Sound.h"
#include <al.h>
#include <alc.h>

#define NUM_BUFFERS 4

Sound::Sound(){
}

Sound::~Sound(){
}

void Sound::init() {
	/*
	alGetError();
	ALCdevice *deviceAL = alcOpenDevice(NULL);
	if (deviceAL == NULL) {
		printf("Failed to init OpenAL device.");
		return;
	}
	// Clear Error Code (so we can catch any new errors)
	alGetError();

	ALuint buffers[NUM_BUFFERS];
	// Create the buffers
	alGenBuffers(NUM_BUFFERS, buffers);
	if (alGetError() != AL_NO_ERROR) {
	  printf("alGenBuffers: error");
	  return;
	}

	ALenum     format;
	ALsizei    size;
	ALsizei    freq;
	ALboolean  loop;
	ALvoid*    data;

	//alutLoadWAVFile("exciting_sound.wav", &format, &data, &size, &freq, &loop);
	if (alGetError() != AL_NO_ERROR) {
	  printf("alutLoadWAVFile sound.wav : error");
	  // Delete Buffers
	  alDeleteBuffers(NUM_BUFFERS, buffers);
	  return;
	}


	// Init openAL
	//alutInit(0, NULL);
	// Clear Error Code (so we can catch any new errors)
	alGetError();*/
}