#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include "LTexture.h"

using namespace std;

namespace TetrisLib {

	LTexture::LTexture(void)
	{
		//initialize
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}

	int LTexture::getWidth() {
		return mWidth;
	}

	int LTexture::getHeight() {
		return mHeight;
	}

	void LTexture::free() {
		//free texture if it exists
		if(mTexture != NULL) {
			SDL_DestroyTexture(mTexture);
			mTexture = NULL;
			mWidth = 0;
			mHeight = 0;
		}
	}

	void LTexture::render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
		//set rendering space and render to screen
		SDL_Rect renderQuad = { x, y,  mWidth, mHeight };

		if(clip != NULL) {
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
	}

	bool LTexture::loadFromFile(string path, SDL_Renderer* gRenderer) {
		free();

		//the final texture
		SDL_Texture* newTexture = NULL;

		//load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());

		if (loadedSurface == NULL) {
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//color key image
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

			//create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

			if (newTexture == NULL) {
				printf("Unable to create texture from %s!  SDL Error:%s\n", path.c_str(), SDL_GetError());
			}
			else
			{
				//get image dimensions
				mWidth = loadedSurface->w;
				mHeight = loadedSurface->h;
			}

			SDL_FreeSurface(loadedSurface);
		}

		//return success
		mTexture = newTexture;
		return mTexture != NULL;
	}

	#ifdef _SDL_TTF_H
	bool LTexture::loadFromRenderedText(SDL_Renderer* gRenderer, TTF_Font* font, string textureText, SDL_Color textColor) {
		free();

		SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);

		if (textSurface == NULL) {
			printf("Unable to render text surface!");
		}
		else
		{
			//create texture from surface pixels
			mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

			if(mTexture == NULL) {
				printf("Unable to create texture");
			}
			else
			{
				//get image dimensions
				mWidth = textSurface->w;
				mHeight = textSurface->h;
			}

			//get rid of old surface
			SDL_FreeSurface(textSurface);
		}

		//return success
		return mTexture != NULL;
	}
	#endif

	void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
		//modulate texture
		SDL_SetTextureColorMod(mTexture, red, green, blue);
	}

	void LTexture::setBlendMode(SDL_BlendMode blending) {
		SDL_SetTextureBlendMode(mTexture, blending);
	}

	void LTexture::setAlphaMod(Uint8 alpha) {
		SDL_SetTextureAlphaMod(mTexture, alpha);
	}

	LTexture::~LTexture(void)
	{
		//deallocate
		free();
	}
}