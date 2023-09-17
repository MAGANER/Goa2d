#include"Definitors.hpp"
#ifdef USE_SDL_AUDIO

#ifndef MUSIC_H
#define MUSIC_H
#include"Audio.h"
#include<string>


namespace Goat2d
{
namespace core
{
	class Music : public Audio
	{
		Mix_Music* buffer = nullptr;
	public:
		Music(const std::string& music_file_path)
		{
			buffer = Mix_LoadMUS(music_file_path.c_str());
			if (buffer == NULL)
			{
				print_error("Failed to load music! SDL_mixer Error:");
				write_error("Failed to load music! SDL_mixer Error:");
				ok = false;
			}
			ok = true;
		}
		~Music()
		{
			Mix_FreeMusic(buffer);
		}

		void play() override
		{
			Mix_PlayMusic(buffer, 0);
		}

		void pause() override 
		{ 
			Mix_PauseMusic();
		}

		void stop() override 
		{  
			Mix_HaltMusic();
		}

		void resume() override 
		{
			Mix_ResumeMusic();
		}

	};
};
};
#endif //MUSIC_H

#endif //USE_SDL_AUDIO