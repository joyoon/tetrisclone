#include "Shape.h"

#pragma once

namespace TetrisLib {

	class Line : public Shape
	{
	private:
		void rotate();
	protected:
		void init();
	public:
		Line(void);
		Line(Line const&);
		Line * create() const;
		Line * clone() const;
		Line(void (*onSetCallback) (SDL_Rect* blocks));
		~Line(void);
		void setPosition(int x, int y);
	};

}