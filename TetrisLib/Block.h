#include <SDL.h>
#include "Color.h"

#pragma once

namespace TetrisLib {

class Block
{
private:
	SDL_Rect* block;
	Color color;
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
	Color getColor() const;
	void setColor(Color color);
	SDL_Rect* getSDLBlock();
};

}