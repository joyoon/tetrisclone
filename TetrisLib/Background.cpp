#include "stdafx.h"
#include "Background.h"
#include "Dot.h"
#include "Global.h"

namespace TetrisLib {

	Background::Background(void)
	{
		bgTexture = NULL;
	}

	Background::~Background(void)
	{
	}

	void Background::setTexture(LTexture* texture) {
		this->bgTexture = texture;
	}

	void Background::render(SDL_Renderer* renderer, SDL_Rect* camera) {
		if (camera->x + SCREEN_WIDTH > LEVEL_WIDTH)
			camera->x = 0;

		bgTexture->render(-camera->x, camera->y, renderer);
	}
}