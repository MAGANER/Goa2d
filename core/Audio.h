/*!
\file
\brief abstract class for sounds and music
\author Maganer
\version 0.2
\date 18.09.2023

This class provides interface to play, stop, pause, resume, check is everything correct.
*/
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
	/*!
	\brief abstract class for sound and music
	\author MAGANER
	\date 18.09.2023
	*/
	class Audio
	{
	protected:

		//! true if loaded correctly, otherwise false
		bool ok = false;
	public:
		Audio(){}
		virtual ~Audio(){}

		virtual void play()   = 0;
		virtual void pause()  = 0;
		virtual void stop()   = 0;
		virtual void resume() = 0;

		//! call this function before using any class' method
		bool is_ok()const { return ok; }
	};
};
};
#endif //AUDIO_H

#endif //USE_SDL_AUDIO