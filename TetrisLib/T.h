#include "Shape.h"

#pragma once

namespace TetrisLib {

	class T : public Shape
	{
	private:
		void rotate(int angle);
	protected:
		void init();
	public:
		T(void);
		T(T const&);
		T* create() const;
		T* clone() const;
		T(void (*onSetCallback) (SDL_Rect*));
		~T(void);
		void setPosition(int x, int y);
	};

}