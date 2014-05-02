#include "stdafx.h"
#include "Dot.h"
#include "S.h"
#include "Global.h"

namespace TetrisLib {

	S::S(void)
	{
		WIDTH = BLOCK_WIDTH * 3;
		HEIGHT = BLOCK_WIDTH * 2;

		//initialize blocks
		Block* r1 = new Block();
		r1->setHeight(BLOCK_WIDTH);
		r1->setWidth(BLOCK_WIDTH);
		r1->setXPos(0);
		r1->setYPos(BLOCK_WIDTH);

		Block* r2 = new Block();
		r2->setHeight(BLOCK_WIDTH);
		r2->setWidth(BLOCK_WIDTH);
		r2->setXPos(BLOCK_WIDTH);
		r2->setYPos(BLOCK_WIDTH);

		Block* r3 = new Block();
		r3->setHeight(BLOCK_WIDTH);
		r3->setWidth(BLOCK_WIDTH);
		r3->setXPos(BLOCK_WIDTH);
		r3->setYPos(0);

		Block* r4 = new Block();
		r4->setHeight(BLOCK_WIDTH);
		r4->setWidth(BLOCK_WIDTH);
		r4->setXPos(BLOCK_WIDTH * 2);
		r4->setYPos(0);

		blocks[0] = *r1;
		blocks[1] = *r2;
		blocks[2] = *r3;	//center block
		blocks[3] = *r4;
	}

	S::S(void (*onSetCallback) (SDL_Rect* blocks)) {
		this->onSetCallback = onSetCallback;

		//initialize blocks
		Block r1;
		r1.setHeight(BLOCK_WIDTH);
		r1.setWidth(BLOCK_WIDTH);
		r1.setXPos(BLOCK_WIDTH * 2);
		r1.setYPos(BLOCK_WIDTH * 2);

		Block r2;
		r2.setHeight(BLOCK_WIDTH);
		r2.setWidth(BLOCK_WIDTH);
		r2.setXPos(BLOCK_WIDTH * 3);
		r2.setYPos(BLOCK_WIDTH * 2);

		Block r3;
		r3.setHeight(BLOCK_WIDTH);
		r3.setWidth(BLOCK_WIDTH);
		r3.setXPos(BLOCK_WIDTH * 3);
		r3.setYPos(BLOCK_WIDTH);

		Block r4;
		r4.setHeight(BLOCK_WIDTH);
		r4.setWidth(BLOCK_WIDTH);
		r4.setXPos(BLOCK_WIDTH * 4);
		r4.setYPos(BLOCK_WIDTH);

		blocks[0] = r1;
		blocks[1] = r2;
		blocks[2] = r3;	//center block
		blocks[3] = r4;
	}

	S::~S(void)
	{
		delete [] blocks;
	}

	S* S::create() const {
		return NULL;
	}

	S* S::clone() const {
		return NULL;
	}

	void S::init() {
	}

	void S::rotate() {
		//get center of block (rotate around 3rd block in blocks array)
		int xCenter = blocks[1].getXPos() + BLOCK_WIDTH / 2;
		int yCenter = blocks[1].getYPos() + BLOCK_WIDTH / 2;

		//rotate first block (bottom left corner will become top left point for rotated block)
		int x = blocks[0].getXPos();
		int y = blocks[0].getYPos() + BLOCK_WIDTH;

		//adjust for center
		int xNewAxis = x - xCenter;
		int yNewAxis = y - yCenter;

		//rotate block
		int xRotated = floor(xNewAxis * cos(1.5708) - yNewAxis * sin(1.5708) + 0.5);
		int yRotated = floor(xNewAxis * sin(1.5708) + yNewAxis * cos(1.5708) + 0.5);

		//adjust for center offset
		xRotated = xRotated + xCenter;
		yRotated = yRotated + yCenter;

		//set x, y coords
		blocks[0].setXPos(xRotated);
		blocks[0].setYPos(yRotated);

		//rotate second block (bottom left corner will become top left point for rotated block)
		x = blocks[1].getXPos();
		y = blocks[1].getYPos() + BLOCK_WIDTH;

		//adjust for center
		xNewAxis = x - xCenter;
		yNewAxis = y - yCenter;

		//rotate block
		xRotated = floor(xNewAxis * cos(1.5708) - yNewAxis * sin(1.5708) + 0.5);
		yRotated = floor(xNewAxis * sin(1.5708) + yNewAxis * cos(1.5708) + 0.5);

		//adjust for center offset
		xRotated = xRotated + xCenter;
		yRotated = yRotated + yCenter;

		//set x, y coords
		blocks[1].setXPos(xRotated);
		blocks[1].setYPos(yRotated);

		//rotate third block (bottom left corner will become top left point for rotated block)
		x = blocks[2].getXPos();
		y = blocks[2].getYPos() + BLOCK_WIDTH;

		//adjust for center
		xNewAxis = x - xCenter;
		yNewAxis = y - yCenter;

		//rotate block
		xRotated = floor(xNewAxis * cos(1.5708) - yNewAxis * sin(1.5708) + 0.5);
		yRotated = floor(xNewAxis * sin(1.5708) + yNewAxis * cos(1.5708) + 0.5);

		//adjust for center offset
		xRotated = xRotated + xCenter;
		yRotated = yRotated + yCenter;

		//set x, y coords
		blocks[2].setXPos(xRotated);
		blocks[2].setYPos(yRotated);

		//rotate fourth block (bottom left corner will become top left point for rotated block)
		x = blocks[3].getXPos();
		y = blocks[3].getYPos() + BLOCK_WIDTH;

		//adjust for center
		xNewAxis = x - xCenter;
		yNewAxis = y - yCenter;

		//rotate block
		xRotated = floor(xNewAxis * cos(1.5708) - yNewAxis * sin(1.5708) + 0.5);
		yRotated = floor(xNewAxis * sin(1.5708) + yNewAxis * cos(1.5708) + 0.5);

		//adjust for center offset
		xRotated = xRotated + xCenter;
		yRotated = yRotated + yCenter;

		//set x, y coords
		blocks[3].setXPos(xRotated);
		blocks[3].setYPos(yRotated);
	}

	void S::setPosition(int x, int y) {
		blocks[0].setXPos(x);
		blocks[0].setYPos(y);
		blocks[1].setXPos(x + BLOCK_WIDTH);
		blocks[1].setYPos(y);
		blocks[2].setXPos(x + BLOCK_WIDTH);
		blocks[2].setYPos(y - BLOCK_WIDTH);
		blocks[3].setXPos(x + BLOCK_WIDTH * 2);
		blocks[3].setYPos(y - BLOCK_WIDTH);
	}
}