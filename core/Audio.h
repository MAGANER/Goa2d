
#include"Definitors.hpp"
#ifdef USE_SDL_AUDIO

#include"SDL_mixer.h"
#include"ErrorLogger.h"
#ifndef AUDIO_H
#define AUDIO_H
namespace Goat2d
{
namespace core
{
	class Audio
	{
	protected:
		bool ok = false;
	public:
		Audio(){}
		virtual ~Audio(){}

		virtual void play()   = 0;
		virtual void pause()  = 0;
		virtual void stop()   = 0;
		virtual void resume() = 0;

		bool is_ok()const { return ok; }
	};
};
};
#endif //AUDIO_H

#endif //USE_SDL_AUDIO