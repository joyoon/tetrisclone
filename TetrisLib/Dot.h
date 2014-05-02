//#ifndef Dot_H
//#define Dot_H
//
//#include "SDL.h"
//#include <SDL_image.h>
//#include "LTexture.h"
//#include <vector>
//#include "Circle.cpp"
//
//using namespace std;
//
//namespace TetrisLib {
//
//	class Dot
//	{
//	public:
//		static const int WIDTH = 20;
//		static const int HEIGHT = 20;
//
//		//maximum axis velocity of dot
//		static const int MAX_VELOCITY = 1;
//
//		void handleEvent(SDL_Event& e);
//
//		void move(vector<SDL_Rect>& otherColliders);
//
//		void render(SDL_Renderer* renderer, LTexture* texture, SDL_Rect* clip);
//
//		//collision detector
//		bool checkCollision(vector<SDL_Rect>& box);
//
//		bool checkCollision(Circle c1, Circle c2);
//
//		Dot(int x, int y);
//		Dot(void);
//		Dot(string imagePath, SDL_Renderer* renderer);
//		~Dot(void);
//
//		float getXPos();
//		float getYPos();
//
//		//gets the collision boxes
//		vector<SDL_Rect>& getColliders();
//	private:
//		//area of the dot
//		Circle dot;
//		float mXPos, mYPos;
//
//		//velocity of the dot
//		float mXVel, mYVel;
//
//		//dot's collision boxes
//		vector<SDL_Rect> mColliders;
//
//		//moves the collision boxes relative to dot's offset
//		void shiftColliders();
//
//		//sets the camera over the dot
//		void setCamera(SDL_Rect& camera);
//	};
//}
//
//#endif