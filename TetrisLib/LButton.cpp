#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include "LButton.h"
#include "LTexture.h"

using namespace std;

namespace TetrisLib {

	LButton::LButton(void)
	{
		mPosition.x = 0;
		mPosition.y = 0;

		mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
	}

	void LButton::handleEvent(SDL_Event* e) {
		//if mouse event happened
		if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
			//get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);

			//check if mouse is in button
			bool inside = true;

			//mouse is left of the button
			if(x < mPosition.x) {
				inside = false;
			}
			//mouse is right of button
			else if (x > mPosition.x + BUTTON_WIDTH) {
				inside = false;
			}
			//mouse above the button
			else if (y < mPosition.y) {
				inside = false;
			}
			//mouse below the button
			else if (y > mPosition.y + BUTTON_HEIGHT) {
				inside = false;
			}

			if (!inside) {
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
			}
			//mouse is inside button
			else
			{
				//set mouse over sprite
				switch(e->type) {
					case SDL_MOUSEMOTION:
						mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
						break;

					case SDL_MOUSEBUTTONDOWN:
						mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
						break;

					case SDL_MOUSEBUTTONUP:
						mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
						break;
				}
			}
		}
	}

	void LButton::render(LTexture* texture, SDL_Renderer* gRenderer, SDL_Rect* gSpriteClips = NULL) {
		texture->render(mPosition.x, mPosition.y, gRenderer, &gSpriteClips[mCurrentSprite]);
	}

	void LButton::setPosition(int x, int y) {
		mPosition.x = x;
		mPosition.y = y;
	}

	LButton::~LButton(void)
	{
	}
}