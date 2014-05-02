//#include "stdafx.h"
//#include "Dot.h"
//#include <SDL.h>
//#include <vector>
//#include "Global.h"
//
//using namespace std;
//
//namespace TetrisLib {
//
//	double distanceSquared(int x1, int y1, int x2, int y2) {
//		int deltaX = x2 - x1;
//		int deltaY = y2 - y1;
//
//		return deltaX * deltaX + deltaY * deltaY;
//	}
//
//	Dot::Dot(void) {
//		Dot(0, 0);
//	}
//
//	Dot::Dot(int x, int y) {
//		mXPos = x;
//		mYPos = y;
//
//		mXVel = 0;
//		mYVel = 0;
//
//		//initialize circle
//		dot.r = 10;
//		dot.x = 20;
//		dot.y = 30;
//
//		mColliders.resize(11);
//
//		//intialize the collision boxes' width/height
//		mColliders[0].w = 6;
//		mColliders[0].h = 1;
//
//		mColliders[1].w = 10;
//		mColliders[1].h = 1;
//
//		mColliders[2].w = 14;
//		mColliders[2].h = 1;
//
//		mColliders[3].w = 14;
//		mColliders[3].h = 2;
//
//		mColliders[4].w = 14;
//		mColliders[4].h = 2;
//
//		mColliders[5].w = 20;
//		mColliders[5].h = 3;
//
//		mColliders[6].w = 13;
//		mColliders[6].h = 2;
//
//		mColliders[7].w = 14;
//		mColliders[7].h = 2;
//
//		mColliders[8].w = 14;
//		mColliders[8].h = 1;
//
//		mColliders[9].w = 10;
//		mColliders[9].h = 1;
//
//		mColliders[10].w = 6;
//		mColliders[10].h = 1;
//
//		shiftColliders();
//	}
//
//	Dot::~Dot(void)
//	{
//	}
//
//	float Dot::getXPos() {
//		return mXPos;
//	}
//
//	float Dot::getYPos() {
//		return mYPos;
//	}
//
//	void Dot::render(SDL_Renderer* renderer, LTexture* texture, SDL_Rect* clip) {
//		texture->render(mXPos, mYPos, renderer, clip);
//	}
//
//	void Dot::handleEvent(SDL_Event& e) {
//		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
//			switch(e.key.keysym.sym) {
//				case SDLK_UP:
//					mYVel -= MAX_VELOCITY;
//					break;
//				case SDLK_DOWN:
//					mYVel += MAX_VELOCITY;
//					break;
//				case SDLK_LEFT:
//					mXVel -= MAX_VELOCITY;
//					break;
//				case SDLK_RIGHT:
//					mXVel += MAX_VELOCITY;
//					break;
//			}
//		}
//	}
//
//	void Dot::move(vector<SDL_Rect>& otherColliders) {
//
//		mXPos += mXVel;
//		//shiftColliders();
//
//		//check if x position is outside screen boundaries
//		if (mXPos < 0 || (mXPos + WIDTH ) > LEVEL_WIDTH) {
//			//move back
//			mXPos -= mXVel;
//			//shiftColliders();
//		}
//
//		mYPos += mYVel;
//
//		//check if y position is outside screen boundaries
//		if (mYPos < 0 || (mYPos + HEIGHT ) > LEVEL_HEIGHT) {
//			//move back
//			mYPos -= mYVel;
//			//shiftColliders();
//		}
//	}
//
//	/*	checkCollision
//	 *	checks for collision between two circles
//	*/
//	bool Dot::checkCollision(Circle c1, Circle c2) {
//		int totalRadiusSquared = c1.r + c2.r;
//
//		if (distanceSquared(c1.x, c1.y, c2.x, c2.y) < totalRadiusSquared * totalRadiusSquared) {
//			return true;
//		}
//	}
//
//	/*	checkCollision
//	 *	checks for collision between circle and given collision boxes
//	*/
//	bool Dot::checkCollision(vector<SDL_Rect>& boxes) {
//		//closest point on rectangle to circle
//		int cX = 0, cY = 0;
//
//		//go through the boxes
//		for (int i = 0; i < boxes.size(); i++) {
//			//find point on rectangle closest to circle
//
//			//get x
//			if (mXPos < boxes[i].x) {
//				cX = boxes[i].x;
//			}
//			else if (mXPos > boxes[i].x + boxes[i].w)
//			{
//				cX = boxes[i].x + boxes[i].w;
//			}
//			else
//			{
//				cX = mXPos;
//			}
//
//			//get y offset
//			if (mYPos >= boxes[i].y + boxes[i].h) {
//				cY = boxes[i].y + boxes[i].h;
//			}
//			else if(mYPos < boxes[i].y)
//			{
//				cY = boxes[i].y;
//			}
//			else
//			{
//				cY = mYPos;
//			}
//
//			if (distanceSquared(mXPos, mYPos, cX, cY) <= dot.r * dot.r)
//				return true;
//		}
//
//		return false;
//	}
//
//	void Dot::shiftColliders() {
//		//row offset
//		int r = 0;
//
//		//shift collider boxes
//		for(int i = 0; i < mColliders.size(); i++) {
//			//center the collision box
//			mColliders[i].x = mXPos + (WIDTH - mColliders[i].w) / 2;
//
//			//set the collision box at its row offset
//			mColliders[i].y = mYPos + r;
//
//			//move the row offset down the height of the collision box
//			r += mColliders[i].h;
//		}
//	}
//
//	void Dot::setCamera(SDL_Rect& camera) {
//		//center camera over dot
//		camera.x = (mXPos + WIDTH / 2) - SCREEN_WIDTH / 2;
//		camera.y = (mYPos + HEIGHT / 2) - SCREEN_HEIGHT / 2;
//
//		//keep the camera in bounds
//		if (camera.x < 0)
//			camera.x = 0;
//
//		if (camera.y < 0)
//			camera.y = 0;
//
//		if (camera.x > LEVEL_WIDTH - camera.w) {
//			camera.x = LEVEL_WIDTH - camera.w;
//		}
//
//		if (camera.y > LEVEL_HEIGHT - camera.h) {
//			camera.y = LEVEL_HEIGHT - camera.h;
//		}
//	}
//
//	vector<SDL_Rect>& Dot::getColliders() {
//		return mColliders;
//	}
//}