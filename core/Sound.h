#include"Definitors.hpp"
#ifdef USE_SDL_AUDIO

#ifndef SOUND_H
#define SOUND_H
#include"Audio.h"
#include<string>
namespace Goat2d
{
namespace core
{
	class Sound: public Audio
	{
		Mix_Chunk* buffer = nullptr;
	public:
		Sound(const std::string& sound_file_path)
		{
			buffer = Mix_LoadWAV(sound_file_path.c_str());
			if (buffer == NULL)
			{
				print_error("Failed to load scratch sound effect! SDL_mixer Error:");
				write_error("Failed to load scratch sound effect! SDL_mixer Error:");
				ok = false;
			}
			ok = true;
		}
		~Sound()
		{
			if (buffer != nullptr)
				Mix_FreeChunk(buffer);
		}


		void play() override
		{
			Mix_PlayChannel(-1, buffer, 0);
		}


		[[deprecated("There is no need to pause sounds!")]]
		void pause() override{return;}

		[[deprecated("There is no need to stop sounds!")]]
		void stop() override{return;}

		[[deprecated("There is no need to stop sounds!")]]
		void resume() override { return; }
	};
};
};
#endif //SOUND_H

#endif //USE_SDL_AUDIO