#include "LTexture.h"

#pragma once

namespace TetrisLib {

class Background
{
public:
	Background(void);
	~Background(void);

	void render(SDL_Renderer* renderer, SDL_Rect* camera);

	void setTexture(LTexture* bgTexture);
private:
	LTexture* bgTexture;
};
}