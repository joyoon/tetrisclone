#include "Shape.h"

using namespace std;

#pragma once

namespace TetrisLib {

	class Square : public Shape
	{
	protected:
		void init();
	public:
		Square(void);
		Square(Square const&);
		Square* create() const;
		Square* clone() const;
		Square(void (*onSetCallback)(SDL_Rect* blocks));
		~Square(void);
		void rotate(int angle);
		void setPosition(int x, int y);
	};

}