#include <string>
#include <SDL.h>
#include "LTexture.h"

using namespace std;

#pragma once

namespace TetrisLib {

	class StringInput
	{
	private:
		//the storage string
		string input;

		//the text surface
		LTexture* texture;
	public:
		StringInput(void);
		~StringInput(void);

		//handles input
		void handle_input(SDL_Event& e);

		//shows the message on the screen
		void render(SDL_Renderer* renderer);

		//loads the text
		void loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font);
	};
}