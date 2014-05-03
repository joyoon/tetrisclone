#include "Shape.h"

#pragma once

namespace TetrisLib {

	class S : public Shape
	{
	protected:
		void rotate(int angle);
		void init();
	public:
		S(void);
		S(void (*onSetCallback) (SDL_Rect* blocks));
		~S(void);
		S* create() const;
		S* clone() const;
		void setPosition(int x, int y);
	};

}