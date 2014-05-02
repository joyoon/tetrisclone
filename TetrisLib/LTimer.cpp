#include "stdafx.h"
#include "LTimer.h"

namespace TetrisLib {
	LTimer::LTimer(void)
	{
		mStarted = false;
		mPaused = false;
		mPausedTicks = 0;
		mStartTicks = 0;
	}

	LTimer::~LTimer(void)
	{
	}

	void LTimer::start() {
		mStarted = true;
		mPaused = false;

		mStartTicks = SDL_GetTicks();
		mPausedTicks = 0;
	}

	void LTimer::stop() {
		mStarted = false;

		mPaused = false;
		mStartTicks = SDL_GetTicks();
		mPausedTicks = 0;
	}

	void LTimer::pause() {
		if (mStarted && !mPaused) {
			mPaused = true;

			mPausedTicks = SDL_GetTicks() - mPausedTicks;
			mStartTicks = 0;
		}
	}

	void LTimer::unpause() {
		if(mPaused) {
			mPaused = false;
			mStartTicks = SDL_GetTicks() - mPausedTicks;

			mPausedTicks = 0;
		}
	}

	Uint32 LTimer::getTicks() {
		//the actual timer time
		Uint32 time = 0;

		if (mStarted) {
			if (mPaused) {
				time = mPausedTicks;
			}
			else {
				time = SDL_GetTicks() - mStartTicks;
			}
		}

		return time;
	}

	bool LTimer::isStarted() {
		return mStarted;
	}

	bool LTimer::isPaused() {
		return mPaused && mStarted;
	}
}