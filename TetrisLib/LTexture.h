#ifndef LTexture_H
#define LTexture_H

#include <SDL_ttf.h>
#include <string>

using namespace std;

namespace TetrisLib {

class LTexture
{
public:
	//initializes variables
	LTexture(void);

	//deallocates memory
	~LTexture(void);

	//loads image at specified path
	bool loadFromFile(string path, SDL_Renderer* gRenderer);

	//creates image from font string
	#ifdef _SDL_TTF_H
	bool loadFromRenderedText(SDL_Renderer* gRenderer, TTF_Font* font, string textureText, SDL_Color textColor);
	#endif

	//deallocates texture
	void free();

	//set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//set color modulation
	void setBlendMode(SDL_BlendMode blending);

	//set alpha modulation
	void setAlphaMod(Uint8 alpha);

	//renders texture at given point
	void render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL, double angle = 0, SDL_Point* point = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//gets image dimensions
	int getWidth();
	int getHeight();

private:
	//the actual hardware texture
	SDL_Texture* mTexture;

	//image dimensions
	int mWidth;
	int mHeight;
};
}

#endif