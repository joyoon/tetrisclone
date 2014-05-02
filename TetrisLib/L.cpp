#include "stdafx.h"
#include "Dot.h"
#include "L.h"
#include <math.h>
#include "Global.h"

namespace TetrisLib {

	L::L(void)
	{
		WIDTH = BLOCK_WIDTH * 3;
		HEIGHT = BLOCK_WIDTH * 2;
		this->onSetCallback = onSetCallback;

		Block* r1 = new Block();
		r1->setXPos(0);
		r1->setYPos(0);
		r1->setWidth(BLOCK_WIDTH);
		r1->setHeight(BLOCK_WIDTH);

		Block* r2 = new Block();
		r2->setXPos(0);
		r2->setYPos(BLOCK_WIDTH);
		r2->setWidth(BLOCK_WIDTH);
		r2->setHeight(BLOCK_WIDTH);

		Block* r3 = new Block();
		r3->setXPos(BLOCK_WIDTH);
		r3->setYPos(BLOCK_WIDTH);
		r3->setWidth(BLOCK_WIDTH);
		r3->setHeight(BLOCK_WIDTH);

		Block* r4 = new Block();
		r4->setXPos(BLOCK_WIDTH * 2);
		r4->setYPos(BLOCK_WIDTH);
		r4->setWidth(BLOCK_WIDTH);
		r4->setHeight(BLOCK_WIDTH);

		blocks[0] = *r1;
		blocks[1] = *r2;
		blocks[2] = *r3;
		blocks[3] = *r4;
	}

	L::~L(void)
	{
		delete [] blocks;
	}

	L::L(void (*onSetCallback) (SDL_Rect* blocks)) {
	}

	void L::init() {
	}

	void L::rotate() {
		//calculate center of block
		int xCenter = blocks[2].getXPos() + BLOCK_WIDTH / 2;
		int yCenter = blocks[2].getYPos() + BLOCK_WIDTH / 2;

		//rotate first block

		//bottom left corner of block will become new top left for rotated block

		//get x, y coords based on new axis
		int xNewAxis = blocks[0].getXPos() - xCenter;
		int yNewAxis = blocks[0].getYPos() - yCenter + BLOCK_WIDTH;

		//rotate
		int xRotated = floor(xNewAxis * cos(1.5708) - yNewAxis * sin(1.5708) + 0.5);
		int yRotated = floor(xNewAxis * sin(1.5708) + yNewAxis * cos(1.5708) + 0.5);

		//adjust for center offset
		blocks[0].setXPos(xCenter + xRotated);
		blocks[0].setYPos(yCenter + yRotated);

		//rotate second block

		//get x, y coords based on new axis
		xNewAxis = blocks[1].getXPos() - xCenter;
		yNewAxis = blocks[1].getYPos() - yCenter + BLOCK_WIDTH;

		//rotate
		xRotated = floor(xNewAxis * cos(1.5708) - yNewAxis * sin(1.5708) + 0.5);
		yRotated = floor(xNewAxis * sin(1.5708) + yNewAxis * cos(1.5708) + 0.5);

		//adjust for center offset
		blocks[1].setXPos(xCenter + xRotated);
		blocks[1].setYPos(yCenter + yRotated);

		//rotate third block

		//get x, y coords based on new axis
		xNewAxis = blocks[2].getXPos() - xCenter;
		yNewAxis = blocks[2].getYPos() - yCenter + BLOCK_WIDTH;

		//rotate
		xRotated = floor(xNewAxis * cos(1.5708) - yNewAxis * sin(1.5708) + 0.5);
		yRotated = floor(xNewAxis * sin(1.5708) + yNewAxis * cos(1.5708) + 0.5);

		//adjust for center offset
		blocks[2].setXPos(xCenter + xRotated);
		blocks[2].setYPos(yCenter + yRotated);

		//rotate fourth block

		//get x, y coords based on new axis
		xNewAxis = blocks[3].getXPos() - xCenter;
		yNewAxis = blocks[3].getYPos() - yCenter + BLOCK_WIDTH;

		//rotate
		xRotated = floor(xNewAxis * cos(1.5708) - yNewAxis * sin(1.5708) + 0.5);
		yRotated = floor(xNewAxis * sin(1.5708) + yNewAxis * cos(1.5708) + 0.5);

		//adjust for center offset
		blocks[3].setXPos(xCenter + xRotated);
		blocks[3].setYPos(yCenter + yRotated);
	}

	L* L::create() const {
		return new L();
	}

	L* L::clone() const {
		return new L(*this);
	}

	L::L(L const& other) {
		for (int i = 0; i < 4; i++)
		{
			blocks[i] = other.blocks[i];
		}
	}

	void L::setPosition(int x, int y) {
		blocks[0].setXPos(x);
		blocks[0].setYPos(y);
		blocks[1].setXPos(x);
		blocks[1].setYPos(y + BLOCK_WIDTH);
		blocks[2].setXPos(x + BLOCK_WIDTH);
		blocks[2].setYPos(y + BLOCK_WIDTH);
		blocks[3].setXPos(x + BLOCK_WIDTH * 2);
		blocks[3].setYPos(y + BLOCK_WIDTH);
	}
}