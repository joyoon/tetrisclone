#ifndef LTimer_H
#define LTimer_H

#include <SDL.h>

using namespace std;

namespace TetrisLib {

	class LTimer
	{
	public:
		LTimer(void);

		//the clock actions
		void start();
		void stop();
		void pause();
		void unpause();
		Uint32 getTicks();

		//checks status of timer
		bool isStarted();
		bool isPaused();

		~LTimer(void);

	private:
		//the clock time when the timer started
		Uint32 mStartTicks;

		//ticks stored when paused
		Uint32 mPausedTicks;

		//timer status
		bool mPaused;
		bool mStarted;
	};

}

#endif