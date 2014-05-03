#include "Shape.h"

#pragma once

namespace TetrisLib {

class J : public Shape
{
private:
	void rotate(int angle);
	void setPosition(int x, int y);
	void init();
public:
	J(void);
	J* create() const;
	J* clone() const;
	~J(void);
};

}