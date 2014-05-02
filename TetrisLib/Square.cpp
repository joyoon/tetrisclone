#include "stdafx.h"
#include "Square.h"
#include "Dot.h"
#include "Shape.h"
#include "Global.h"

namespace TetrisLib {

	Square::Square(void)
	{
		isSet = false;
		WIDTH = BLOCK_WIDTH * 2;
		HEIGHT = BLOCK_WIDTH * 2;

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
		r3->setXPos(0);
		r3->setYPos(BLOCK_WIDTH);
		r3->setWidth(BLOCK_WIDTH);
		r3->setHeight(BLOCK_WIDTH);

		Block* r4 = new Block();
		r4->setXPos(BLOCK_WIDTH);
		r4->setYPos(BLOCK_WIDTH);
		r4->setWidth(BLOCK_WIDTH);
		r4->setHeight(BLOCK_WIDTH);

		blocks[0] = *r1;
		blocks[1] = *r2;
		blocks[2] = *r3;
		blocks[3] = *r4;
	}

	Square::Square(void (*onSetCallback)(SDL_Rect* blocks)) {
		this->onSetCallback = onSetCallback;
		isSet = false;
		WIDTH = 128;
		HEIGHT = 128;

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
		r3.setXPos(BLOCK_WIDTH);
		r3.setYPos(BLOCK_WIDTH * 2);
		r3.setWidth(BLOCK_WIDTH);
		r3.setHeight(BLOCK_WIDTH);

		Block r4;
		r4.setXPos(BLOCK_WIDTH * 2);
		r4.setYPos(BLOCK_WIDTH * 2);
		r4.setWidth(BLOCK_WIDTH);
		r4.setHeight(BLOCK_WIDTH);

		blocks[0] = r1;
		blocks[1] = r2;
		blocks[2] = r3;
		blocks[3] = r4;
	}

	Square::~Square(void)
	{
		delete [] blocks;
	}

	void Square::init() {
	}

	void Square::rotate() {
	}

	Square* Square::create() const {
		return new Square();
	}

	Square* Square::clone() const {
		return new Square(*this);
	}

	Square::Square(Square const& other) {
	}

	void Square::setPosition(int x, int y) {
		blocks[0].setXPos(x);
		blocks[0].setYPos(y);
		blocks[1].setXPos(x + BLOCK_WIDTH);
		blocks[1].setYPos(y);
		blocks[2].setXPos(x);
		blocks[2].setYPos(y + BLOCK_WIDTH);
		blocks[3].setXPos(x + BLOCK_WIDTH);
		blocks[3].setYPos(y + BLOCK_WIDTH);
	}
}