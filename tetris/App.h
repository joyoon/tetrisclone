#include "TetrisLib.h"

#pragma once

using namespace TetrisLib;

class App
{
private:
	static const int SCREEN_FPS = 80;
	static const int SCREEN_TICKS_PER_FRAME = 1000/SCREEN_FPS;
	int level;
	int lines;
	int score;
	bool quit;
	bool gameStarted;
	bool gameRunning;
	bool gameOver;
	SDL_Color startMenuTextColor;
	TTF_Font* gFont;
	LTexture* gStartTexture;
	LTexture* gMenuTexture;
	LTexture* gLevelTextTexture;
	LTexture* gLevelTexture;
	LTexture* gLinesTextTexture;
	LTexture* gLinesTexture;
	LTexture* gTextTexture;
	LTexture* gScoreTexture;
	LTexture* gGameOverTexture;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	LTimer capTimer;
	LTimer fpsTimer;
	LTimer blockTimer;
	Uint32 ticks;
	Uint32 ticksBetweenMovement;
	//the current shape
	Shape* curShape;
	Shape* nextShape;
	//the blocks that have been set
	Block*** screenBlocks;
	//an array that maintains the state of the colliders on the screen
	bool** screenColliders;
	void initializeScreenBlocks();
	void initializeScreenColliders();
	void nullScreenColliderLine(int clearedLineYIndex);
	void setScreenColliders(Block* blocks);
	void onBlockSet(Block* blocks);
	void moveBlocksDownAfterClearingLine(int clearedLineYIndex);
	void clearLine(int yIndex);
	bool checkLineCleared(int yIndex);
	bool checkBlockOutOfScreen(Block* blocks);
	bool checkCollision(Block* blocks, bool** screenColliders);
	bool checkForLoss();
	void close();
	Shape* getRandomBlock(int seed = 0);
	void renderShape(Block* blocks);
	bool loadMedia();
public:
	App(void);
	~App(void);

	int onExecute();

	bool onInit();

	void onEvent(SDL_Event* e);

	void onLoop();

	void onRender();

	void onCleanup();
};