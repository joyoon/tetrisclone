#include "stdafx.h"
#include "Line.h"
#include "Global.h"

using namespace std;

namespace TetrisLib {

	Line::Line(void)
	{
		isSet = false;
		WIDTH = BLOCK_WIDTH * 4;
		HEIGHT = BLOCK_WIDTH;

		Block* r1 = new Block();
		r1->setXPos(0);
		r1->setYPos(0);
		r1->setWidth(BLOCK_WIDTH);
		r1->setHeight(BLOCK_WIDTH);

		Block* r2 = new Block();
		r2->setXPos(BLOCK_WIDTH);
		r2->setYPos(0);
		r2->setWidth(BLOCK_WIDTH);
		r2->setHeight(BLOCK_WIDTH);

		Block* r3 = new Block();
		r3->setXPos(BLOCK_WIDTH * 2);
		r3->setYPos(0);
		r3->setWidth(BLOCK_WIDTH);
		r3->setHeight(BLOCK_WIDTH);

		Block* r4 = new Block();
		r4->setXPos(BLOCK_WIDTH * 3);
		r4->setYPos(0);
		r4->setWidth(BLOCK_WIDTH);
		r4->setHeight(BLOCK_WIDTH);

		blocks[0] = *r1;
		blocks[1] = *r2;
		blocks[2] = *r3;
		blocks[3] = *r4;
	}

	Line::Line(void (*onSetCallback) (SDL_Rect* blocks)) {
		this->onSetCallback = onSetCallback;
		isSet = false;
		WIDTH = BLOCK_WIDTH * 4;
		HEIGHT = BLOCK_WIDTH;

		Block r1;
		r1.setXPos(BLOCK_WIDTH);
		r1.setYPos(BLOCK_WIDTH);
		r1.setWidth(BLOCK_WIDTH);
		r1.setHeight(BLOCK_WIDTH);

		Block r2;
		r2.setXPos(BLOCK_WIDTH * 2);
		r2.setYPos(BLOCK_WIDTH);
		r2.setWidth(BLOCK_WIDTH);
		r2.setHeight(BLOCK_WIDTH);

		Block r3;
		r3.setXPos(BLOCK_WIDTH * 3);
		r3.setYPos(BLOCK_WIDTH);
		r3.setWidth(BLOCK_WIDTH);
		r3.setHeight(BLOCK_WIDTH);

		Block r4;
		r4.setXPos(BLOCK_WIDTH * 4);
		r4.setYPos(BLOCK_WIDTH);
		r4.setWidth(BLOCK_WIDTH);
		r4.setHeight(BLOCK_WIDTH);

		blocks[0] = r1;
		blocks[1] = r2;
		blocks[2] = r3;
		blocks[3] = r4;
	}

	Line::~Line(void)
	{
		delete [] blocks;
	}

	void Line::init() {
	}

	void Line::rotate() {
		//get center of block
		int xCenter = blocks[1].getXPos() + BLOCK_WIDTH / 2;
		int yCenter = blocks[1].getYPos() + BLOCK_WIDTH / 2;

		//rotate first block

		//get x, y coords based on center
		int xNewAxis = blocks[0].getXPos() - xCenter;
		int yNewAxis = blocks[0].getYPos() - yCenter;

		//rotate the block
		int xRotated = floor(xNewAxis * cos(1.5708) - yNewAxis * sin(1.5708) + 0.5);
		int yRotated = floor(xNewAxis * sin(1.5708) + yNewAxis * cos(1.5708) + 0.5);

		//adjust for center offset
		blocks[0].setXPos(xCenter - xRotated);
		blocks[0].setYPos(yCenter + yRotated);

		//rotate second block

		//get x, y coords based on center
		xNewAxis = blocks[1].getXPos() - xCenter;
		yNewAxis = blocks[1].getYPos() - yCenter;

		//rotate
		xRotated = floor(xNewAxis * cos(1.5708) - yNewAxis * sin(1.5708) + 0.5);
		yRotated = floor(xNewAxis * sin(1.5708) + yNewAxis * cos(1.5708) + 0.5);

		//adjust for center offset
		blocks[1].setXPos(xCenter - xRotated);
		blocks[1].setYPos(yCenter + yRotated);

		//rotate third block

		//get x, y coords based on center
		xNewAxis = blocks[2].getXPos() - xCenter;
		yNewAxis = blocks[2].getYPos() - yCenter;

		//rotate
		xRotated = floor(xNewAxis * cos(1.5708) - yNewAxis * sin(1.5708) + 0.5);
		yRotated = floor(xNewAxis * sin(1.5708) + yNewAxis * cos(1.5708) + 0.5);

		//adjust for center offset
		blocks[2].setXPos(xCenter - xRotated);
		blocks[2].setYPos(yCenter + yRotated);

		//rotate fourth block

		//get x, y coords based on center
		xNewAxis = blocks[3].getXPos() - xCenter;
		yNewAxis = blocks[3].getYPos() - yCenter;

		//rotate
		xRotated = floor(xNewAxis * cos(1.5708) - yNewAxis * sin(1.5708) + 0.5);
		yRotated = floor(xNewAxis * sin(1.5708) + yNewAxis * cos(1.5708) + 0.5);

		//adjust for center offset
		blocks[3].setXPos(xCenter - xRotated);
		blocks[3].setYPos(yCenter + yRotated);
	}

	Line* Line::create() const {
		return new Line();
	}

	Line* Line::clone() const {
		return new Line(*this);
	}

	Line::Line(Line const& other) {
		for (int i = 0; i < 4; i++)
		{
			blocks[i] = other.blocks[i];
		}
	}

	void Line::setPosition(int x, int y) {
		blocks[0].setXPos(x);
		blocks[0].setYPos(y);
		blocks[1].setXPos(x + BLOCK_WIDTH);
		blocks[1].setYPos(y);
		blocks[2].setXPos(x + BLOCK_WIDTH * 2);
		blocks[2].setYPos(y);
		blocks[3].setXPos(x + BLOCK_WIDTH * 3);
		blocks[3].setYPos(y);
	}
}