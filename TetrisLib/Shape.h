#include <SDL.h>
#include "Block.h"
#include <vector>

#pragma once

namespace TetrisLib {
	class ShapeTypes {
	public:
		enum ShapeType {
			Square = 1,
			Line,
			L,
			J,
			T,
			S,
			Z
		};
	};

	class Shape
	{
	protected:
		ShapeTypes::ShapeType shapeType;
		Color color;
		Block blocks[4];
		void (*onSetCallback) (SDL_Rect* blocks);
		Shape(void);
		int WIDTH, HEIGHT;
		virtual void init() = 0;
		bool checkBlockOutOfScreen();
		bool checkCollision(SDL_Rect* blocks, bool** screenColliders);
	public:
		void handleEvent(SDL_Event e, bool** screenColliders);
		void moveLeft();
		void moveRight();
		void moveDown();
		void moveUp();
		virtual void rotate(int angle) = 0;
		void render(SDL_Renderer* renderer);
		bool isSet;
		Block* getBlocks();
		virtual Shape* create() const = 0;
		virtual Shape* clone() const = 0;
		virtual ~Shape() {};
		Shape(const Shape&);
		virtual void setPosition(int x, int y) = 0;
		int getWidth() const;
		int getHeight() const;
		Color getColor() const;
	};
}