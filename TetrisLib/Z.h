#include "Shape.h"

#pragma once

namespace TetrisLib {

	class Z : public Shape
	{
	private:
		void init();
	protected:
		void rotate();
	public:
		Z(void);
		Z(void (*onSetCallback) (SDL_Rect* blocks));
		~Z(void);
		Z(Z& const);
		Z* clone() const;
		Z* create() const;
		void setPosition(int x, int y);
	};

}