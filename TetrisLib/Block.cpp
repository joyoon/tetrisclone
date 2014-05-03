#include "stdafx.h"
#include "Block.h"
#include "Color.h"

namespace TetrisLib {

Block::Block(void)
{
	block = new SDL_Rect();
}

Block::~Block(void)
{
	delete block;
}

int Block::getXPos() {
	return block->x;
}

int Block::getYPos() {
	return block->y;
}

int Block::getWidth() {
	return block->w;
}

int Block::getHeight() {
	return block->h;
}

void Block::setXPos(int xPos) {
	block->x = xPos;
}

void Block::setYPos(int yPos) {
	block->y = yPos;
}

void Block::setWidth(int width) {
	block->w = width;
}

void Block::setHeight(int height) {
	block->h = height;
}

Color Block::getColor() const {
	return color;
}

void Block::setColor(Color color) {
	this->color = color;
}

SDL_Rect* Block::getSDLBlock() {
	return block;
}

}