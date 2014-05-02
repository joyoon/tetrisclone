#include "stdafx.h"
#include "Shape.h"
#include "Dot.h"
#include "Square.h"
#include "Line.h"
#include "Global.h"

namespace TetrisLib {

	Shape::Shape(void)
	{
	}

	void Shape::handleEvent(SDL_Event e, bool **screenColliders) {
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_RIGHT)
				moveRight();
			else if (e.key.keysym.sym == SDLK_UP)
				rotate();
			else if (e.key.keysym.sym == SDLK_LEFT)
				moveLeft();
			else if (e.key.keysym.sym == SDLK_DOWN) {
				moveDown();
			}
		}
	}

	bool Shape::checkBlockOutOfScreen() {
		for (int i = 0; i < 4; i++)
		{
			if (blocks[i].getXPos() < 0 || blocks[i].getXPos() + blocks[i].getWidth() > SCREEN_WIDTH - BLOCK_WIDTH * 4 || blocks[i].getYPos() + blocks[i].getHeight() > SCREEN_HEIGHT)
				return true;
		}

		return false;
	}

	bool Shape::checkCollision(SDL_Rect* blocks, bool** screenColliders) {
		//arrays to store indexes of blocks
		int xIndexes[4] = { blocks[0].x / 32, blocks[1].x / 32, blocks[2].x / 32, blocks[3].x / 32 };
		int yIndexes[4] = { blocks[0].y / 32, blocks[1].y / 32, blocks[2].y / 32, blocks[3].y / 32 };

		//check if there is a screen collider at x, y indexes
		for (int i = 0; i < 4; i++)
		{
			if (screenColliders[yIndexes[i]][xIndexes[i]] == true)
				return true;
		}

		return false;
	}

	void Shape::moveLeft() {
		blocks[0].setXPos(blocks[0].getXPos() - BLOCK_WIDTH);
		blocks[1].setXPos(blocks[1].getXPos() - BLOCK_WIDTH);
		blocks[2].setXPos(blocks[2].getXPos() - BLOCK_WIDTH);
		blocks[3].setXPos(blocks[3].getXPos() - BLOCK_WIDTH);
	}

	void Shape::moveRight() {
		blocks[0].setXPos(blocks[0].getXPos() + BLOCK_WIDTH);
		blocks[1].setXPos(blocks[1].getXPos() + BLOCK_WIDTH);
		blocks[2].setXPos(blocks[2].getXPos() + BLOCK_WIDTH);
		blocks[3].setXPos(blocks[3].getXPos() + BLOCK_WIDTH);
	}

	void Shape::moveUp() {
		blocks[0].setYPos(blocks[0].getYPos() - BLOCK_WIDTH);
		blocks[1].setYPos(blocks[1].getYPos() - BLOCK_WIDTH);
		blocks[2].setYPos(blocks[2].getYPos() - BLOCK_WIDTH);
		blocks[3].setYPos(blocks[3].getYPos() - BLOCK_WIDTH);
	}

	void Shape::moveDown() {
		//move blocks down
		blocks[0].setYPos(blocks[0].getYPos() + BLOCK_WIDTH);
		blocks[1].setYPos(blocks[1].getYPos() + BLOCK_WIDTH);
		blocks[2].setYPos(blocks[2].getYPos() + BLOCK_WIDTH);
		blocks[3].setYPos(blocks[3].getYPos() + BLOCK_WIDTH);
	}

	Block* Shape::getBlocks() {
		return blocks;
	}

	void Shape::render(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, blocks[0].getSDLBlock());
		SDL_RenderFillRect(renderer, blocks[1].getSDLBlock());
		SDL_RenderFillRect(renderer, blocks[2].getSDLBlock());
		SDL_RenderFillRect(renderer, blocks[3].getSDLBlock());
	}

	Shape::Shape(const Shape& other) {
	}

	void Shape::setPosition(int x, int y) {
		blocks[0].setXPos(blocks[0].getXPos() + x);
		blocks[0].setYPos(blocks[0].getYPos() + y);
		blocks[1].setXPos(blocks[1].getXPos() + x);
		blocks[1].setYPos(blocks[1].getYPos() + y);
		blocks[2].setXPos(blocks[2].getXPos() + x);
		blocks[2].setYPos(blocks[2].getYPos() + y);
		blocks[3].setXPos(blocks[3].getXPos() + x);
		blocks[3].setYPos(blocks[3].getYPos() + y);
	}

	int Shape::getHeight() const {
		return HEIGHT;
	}

	int Shape::getWidth() const {
		return WIDTH;
	}
}