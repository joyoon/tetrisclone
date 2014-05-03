#include "Shape.h"
#include <vector>

#pragma once

namespace TetrisLib {

	class L : public Shape
	{
	private:
		void rotate(int angle);
	protected:
		void init();
	public:
		L(void (*onSetCallback) (SDL_Rect* blocks));
		L(L const&);
		L* create() const;
		L* clone() const;
		L(void);
		~L(void);
		void setPosition(int x, int y);
	};

}