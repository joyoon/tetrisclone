#include "stdafx.h"
#include "StringInput.h"
#include <SDL.h>

namespace TetrisLib {

	StringInput::StringInput(void)
	{
		//initialize variables
		input = "";
		texture = new LTexture();
	}

	StringInput::~StringInput(void)
	{

	}

	void StringInput::handle_input(SDL_Event& e) {
		if(e.type == SDL_KEYDOWN) {
			string temp = input;

			//handle backspace
			if (e.key.keysym.sym == SDLK_BACKSPACE && input.length() > 0) {
				input.pop_back();
			}
			else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
				input = SDL_GetClipboardText();
			}
			else {
				//check not pasting
				if (!((e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {
					//append character
					input += e.key.keysym.sym;
				}
			}
		}
	}

	void StringInput::loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font) {
		//render text
		SDL_Color textColor = { 0, 0, 0 };

		//load ttf text
		if (!texture->loadFromRenderedText(renderer, font, input, textColor)) {
			printf("could not load text!");
		}
	}

	void StringInput::render(SDL_Renderer* renderer) {
		texture->render(0, 0, renderer);
	}
}