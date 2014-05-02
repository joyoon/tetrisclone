#include <SDL.h>

#pragma once

namespace TetrisLib {

class Block
{
private:
	SDL_Rect* block;
public:
	Block(void);
	~Block(void);
	int getXPos();
	int getYPos();
	int getWidth();
	int getHeight();
	void setXPos(int x);
	void setYPos(int y);
	void setWidth(int w);
	void setHeight(int h);
	SDL_Rect* getSDLBlock();
};

}