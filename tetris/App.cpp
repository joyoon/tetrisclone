#include "App.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <SDL_image.h>
#include "LTexture.h"

using namespace std;
using namespace TetrisLib;

App::App(void)
{
	gWindow = NULL;
	gRenderer = NULL;
	level = 1;
	lines = 0;
	score = 0;
	quit = false;
	ticks = 0;
	ticksBetweenMovement = 700;
	gTextTexture = new LTexture();
	gScoreTexture = new LTexture();
	gLevelTextTexture = new LTexture();
	gLevelTexture = new LTexture();
	gLinesTextTexture = new LTexture();
	gLinesTexture = new LTexture();
}

App::~App(void)
{
}

int main(int argc, char* args[] )
{
	App app;
	return app.onExecute();
}

int App::onExecute() {
	//start up SDL and create window
	if(!onInit())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		initializeScreenColliders();
		initializeScreenBlocks();

		//initialize first shape
		Shape* s = getRandomBlock();
		s->setPosition(192, 64);

		//add new shape to the shapes array
		shapes.push_back(s);

		curShape = shapes.back();

		//initialize next shape
		nextShape = getRandomBlock(3);

		//calculate x position based on width of shape
		int width = nextShape->getWidth();
		int xPos = (192 - width) / 2;

		nextShape->setPosition(xPos, 352);

		//event handler
		SDL_Event e;

		//start timer
		blockTimer.start();

		//while application is running
		while(!quit) {

			//handle events on queue
			while(SDL_PollEvent(&e) != 0) {
				onEvent(&e);
			}

			onLoop();

			onRender();
		}
	}

	//free resources and close SDL
	close();

	return 0;
}

void App::onEvent(SDL_Event* e) {

	Shape* curShape = NULL;
	curShape = shapes.back();

	//user requests quit
	if(e->type == SDL_QUIT) {
		quit = true;
	}
	else if (e->type == SDL_KEYDOWN) {

		switch (e->key.keysym.sym)
		{
			case SDLK_UP:
				curShape->rotate(90);

				//check if rotation causes collision
				if (checkBlockOutOfScreen(curShape->getBlocks())) {
					//rotate the block back
					curShape->rotate(90);
					curShape->rotate(90);
					curShape->rotate(90);
				}
				break;
			case SDLK_RIGHT:
				curShape->moveRight();

				if(checkBlockOutOfScreen(curShape->getBlocks())) {
					//move blocks back
					curShape->moveLeft();

					break;
				}

				//check collision
				if (checkCollision(curShape->getBlocks(), screenColliders))
					curShape->moveLeft();

				break;
			case SDLK_LEFT:
				curShape->moveLeft();

				if(checkBlockOutOfScreen(curShape->getBlocks())) {
					//move blocks back
					curShape->moveRight();

					break;
				}

				//check collision
				if (checkCollision(curShape->getBlocks(), screenColliders))
					curShape->moveRight();

				break;
			case SDLK_DOWN:
				curShape->moveDown();

				//check if block is out of screen
				if(checkBlockOutOfScreen(curShape->getBlocks())) {
					//if block is out of screen

					//move blocks back
					curShape->moveUp();

					onBlockSet(curShape->getBlocks());

					return;
				}

				//check for collision with other block
				if (checkCollision(curShape->getBlocks(), screenColliders)) {
					curShape->moveUp();

					onBlockSet(curShape->getBlocks());
				}

				break;
			default:
				break;
		}
	}
}

void App::onLoop() {
	capTimer.start();

	Shape* curShape = NULL;
	curShape = shapes.back();

	if (blockTimer.getTicks() > ticks + ticksBetweenMovement) {
		ticks = blockTimer.getTicks();

		curShape->moveDown();

		//check if block is out of screen
		if(checkBlockOutOfScreen(curShape->getBlocks())) {
			//if block is out of screen

			//move blocks back
			curShape->moveUp();

			Block* curShapeBlocks = curShape->getBlocks();

			onBlockSet(curShapeBlocks);

			return;
		}

		//check for collision with other block
		if (checkCollision(curShape->getBlocks(), screenColliders)) {
			curShape->moveUp();

			Block* curShapeBlocks = curShape->getBlocks();

			//add blocks to screenBlocks array
			for (int i = 0; i < 4; i++)
			{
				screenBlocks[curShapeBlocks[i].getYPos() / 32][curShapeBlocks[i].getXPos() / 32] = &curShapeBlocks[i];
			}

			//add collision boxes to screencolliders array
			setScreenColliders(curShape->getBlocks());

			//check if any lines were cleared
			for (int i = 0; i < 4; i++)
			{
				if(checkLineCleared(curShape->getBlocks()[i].getYPos() / 32)) {
					//clear the line
					clearLine(curShapeBlocks[i].getYPos() / 32);

					//clear screen state
					nullScreenColliderLine(curShapeBlocks[i].getYPos() / 32);

					//move blocks above the line down
					moveBlocksDownAfterClearingLine(curShapeBlocks[i].getYPos() / 32);
				}
			}

			//create a new shape
			Shape* s = getRandomBlock();

			s->setPosition(192, 32);

			//add new shape to shapes array
			shapes.push_back(s);
		}
	}
}

void App::onRender() {
	//define viewports for game and legend
	SDL_Rect gameViewPort;
	SDL_Rect legendViewport;

	gameViewPort.x = 0;
	gameViewPort.y = 0;
	gameViewPort.w = BLOCK_WIDTH * 14;
	gameViewPort.h = SCREEN_HEIGHT;

	legendViewport.x = BLOCK_WIDTH * 14;
	legendViewport.y = 0;
	legendViewport.w = BLOCK_WIDTH * 6;
	legendViewport.h = SCREEN_HEIGHT;

	SDL_RenderClear(gRenderer);

	//render background
	SDL_Rect gameBackground = { 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH };

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	SDL_RenderFillRect(gRenderer, &gameBackground);

	SDL_RenderSetViewport(gRenderer, &gameViewPort);

	//render the current shape
	renderShape(curShape->getBlocks());

	//render set shapes
	for (int i = 0; i < SCREEN_HEIGHT / 32; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH / 32 - 6; j++)
		{
			if (screenBlocks[i][j] != NULL) {

				switch (screenBlocks[i][j]->getColor())
				{
					case Color::Blue:
						SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
						break;
					case Color::Green:
						SDL_SetRenderDrawColor(gRenderer, 0x00, 0x80, 0x00, 0xFF);
						break;
					case Color::Orange:
						SDL_SetRenderDrawColor(gRenderer, 0xF8, 0x72, 0x17, 0xFF);
						break;
					case Color::Purple:
						SDL_SetRenderDrawColor(gRenderer, 0x7D, 0x05, 0x41, 0xFF);
						break;
					case Color::Red:
						SDL_SetRenderDrawColor(gRenderer, 0x99, 0x00, 0x12, 0xFF);
						break;
					case Color::Turqoise:
						SDL_SetRenderDrawColor(gRenderer, 0x3B, 0x9C, 0x9C, 0xFF);
						break;
					case Color::Yellow:
						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
						break;
					default:
						break;
				}

				SDL_RenderFillRect(gRenderer, screenBlocks[i][j]->getSDLBlock());
			}
		}
	}

	//render legend
	SDL_RenderSetViewport(gRenderer, &legendViewport);

	//render background
	SDL_Rect background = { 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH };

	SDL_SetRenderDrawColor(gRenderer, 0xB2, 0xB2, 0xB2, 0xB2);

	SDL_RenderFillRect(gRenderer, &background);

	//render score
	gTextTexture->render(60, 32, gRenderer);

	gScoreTexture->render(60, 64, gRenderer);

	//render level
	gLevelTextTexture->render(60, 128, gRenderer);

	gLevelTexture->render(60, 160, gRenderer);

	//render lines
	gLinesTextTexture->render(60, 224, gRenderer);

	gLinesTexture->render(60, 256, gRenderer);

	//render next block
	renderShape(nextShape->getBlocks());

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//update screen
	SDL_RenderPresent(gRenderer);
}

bool App::onInit() {
	//initialization flag
	bool success = true;

	//initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not initialize! SDL_Error:%s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL) {
			printf("Window could not be created!  SDL_Error:%\n", SDL_GetError());
			success = false;
		}
		else
		{
			//create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (gRenderer == NULL) {
				printf("Renderer could not be created!  SDL error: %S\n", SDL_GetError());
				success = false;
			}
			else
			{
				//initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//initialize PNG loading
				//int imgFlags = IMG_INIT_PNG;

				//if(!(IMG_Init(imgFlags) & imgFlags)) {
				//	printf("SDL_image could not initialize!  SDL_image Error: %s\n", IMG_GetError());
				//	success = false;
				//}

				 //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

				loadMedia();
			}
		}
	}

	return success;
}

void App::renderShape(Block* blocks) {

	switch (blocks[0].getColor())
	{
		case Color::Blue:
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
			break;
		case Color::Green:
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x80, 0x00, 0xFF);
			break;
		case Color::Orange:
			SDL_SetRenderDrawColor(gRenderer, 0xF8, 0x72, 0x17, 0xFF);
			break;
		case Color::Purple:
			SDL_SetRenderDrawColor(gRenderer, 0x7D, 0x05, 0x41, 0xFF);
			break;
		case Color::Red:
			SDL_SetRenderDrawColor(gRenderer, 0x99, 0x00, 0x12, 0xFF);
			break;
		case Color::Turqoise:
			SDL_SetRenderDrawColor(gRenderer, 0x3B, 0x9C, 0x9C, 0xFF);
			break;
		case Color::Yellow:
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
			break;
		default:
			break;
	}

	SDL_RenderFillRect(gRenderer, blocks[0].getSDLBlock());
	SDL_RenderFillRect(gRenderer, blocks[1].getSDLBlock());
	SDL_RenderFillRect(gRenderer, blocks[2].getSDLBlock());
	SDL_RenderFillRect(gRenderer, blocks[3].getSDLBlock());
}

void App::initializeScreenColliders() {
	//initialize screen colliders array
	screenColliders = new bool*[SCREEN_HEIGHT / 32];

	for (int i = 0; i < SCREEN_HEIGHT / 32; i++)
		screenColliders[i] = new bool[SCREEN_WIDTH / 32 - 6];

	//initialize screen colliders values
	for (int i = 0; i < SCREEN_HEIGHT / 32; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH / 32 - 6; j++)
		{
			screenColliders[i][j] = false;
		}
	}
}

void App::initializeScreenBlocks() {
	//initialize screen blocks array
	screenBlocks = new Block**[SCREEN_HEIGHT / 32];

	for (int i = 0; i < SCREEN_HEIGHT / 32; i++)
		screenBlocks[i] = new Block*[SCREEN_WIDTH / 32 - 6];

	//initialize screen blocks values
	for (int i = 0; i < SCREEN_HEIGHT / 32; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH / 32 - 6; j++)
		{
			screenBlocks[i][j] = NULL;
		}
	}
}

Shape* App::getRandomBlock(int seed) {
	//generate random number between 1 and 4
	if (seed == 0)
		srand(time(NULL));
	else
		srand(time(NULL) + 3);

	int r = rand() % 7 + 1;
	ShapeTypes::ShapeType shapeType = (ShapeTypes::ShapeType) r;

	switch (shapeType)
	{
		case ShapeTypes::Square:
			return new Square();
			break;

		case ShapeTypes::Line:
			return new Line();
			break;

		case ShapeTypes::L:
			return new L();
			break;

		case ShapeTypes::J:
			return new J();
			break;

		case ShapeTypes::T:
			return new T();
			break;

		case ShapeTypes::S:
			return new S();
			break;

		case ShapeTypes::Z:
			return new Z();
			break;

		default:
			break;
	}
}

void App::nullScreenColliderLine(int clearedLineYIndex) {
	for (int i = 0; i < SCREEN_WIDTH / 32 - 6; i++)
	{
		screenColliders[clearedLineYIndex][i] = NULL;
	}
}

void App::setScreenColliders(Block* blocks) {
	int xIndex = 0, yIndex = 0;

	for (int i = 0; i < 4; i++) {
		xIndex = blocks[i].getXPos() / 32;
		yIndex = blocks[i].getYPos() / 32;
		screenColliders[yIndex][xIndex] = true;
	}
}

void App::onBlockSet(Block* blocks) {

	//add blocks to screenBlocks array
	for (int i = 0; i < 4; i++)
	{
		screenBlocks[blocks[i].getYPos() / 32][blocks[i].getXPos() / 32] = &shapes.back()->getBlocks()[i];
	}

	//add collision boxes to screencolliders array
	setScreenColliders(blocks);

	//check if any lines were cleared
	for (int i = 0; i < 4; i++)
	{
		if(checkLineCleared(blocks[i].getYPos() / 32)) {
			//clear the line
			clearLine(blocks[i].getYPos() / 32);

			//clear screen state
			nullScreenColliderLine(blocks[i].getYPos() / 32);

			//move blocks above the line down
			moveBlocksDownAfterClearingLine(blocks[i].getYPos() / 32);

			SDL_Color textColor = { 0, 0, 0 };

			//update score
			score += 50;

			//update lines
			lines++;

			//update level
			if (score >= 1000) {
				level = 5;
				ticksBetweenMovement = 300;
			}
			else if (score >= 700) {
				level = 4;
				ticksBetweenMovement = 400;
			}
			else if (score >= 400) {
				level = 3;
				ticksBetweenMovement = 500;
			}
			else if (score >= 200) {
				level = 2;
				ticksBetweenMovement = 600;
			}

			//update the score
			gScoreTexture->loadFromRenderedText(gRenderer, gFont, to_string(score), textColor);

			//update the level
			gLevelTexture->loadFromRenderedText(gRenderer, gFont, to_string(level), textColor );

			//update the lines
			gLinesTexture->loadFromRenderedText(gRenderer, gFont, to_string(lines), textColor );
		}
	}

	//add next shape to shapes array
	shapes.push_back(nextShape);

	curShape = shapes.back();

	//set the position of the block
	curShape->setPosition(192, 32);

	//instantiate next block
	nextShape = getRandomBlock();

	//calculate x position of next shape
	int width = nextShape->getWidth();
	int xPos = (192 - width) / 2;

	nextShape->setPosition(xPos, 352);
}

void App::moveBlocksDownAfterClearingLine(int clearedLineYIndex) {
	//move screen blocks - start at line above cleared line
	for (int i = clearedLineYIndex - 1; i >= 0; i--)
	{
		for (int j = 0; j < SCREEN_WIDTH / 32 - 6; j++)
		{
			if (screenBlocks[i][j] != NULL) {
				//copy block above current line into current line
				screenBlocks[i + 1][j] = screenBlocks[i][j];

				//set y coord
				screenBlocks[i + 1][j]->setYPos((i + 1) * 32);

				//set copied block to NULL
				screenBlocks[i][j] = NULL;

				//set screen collider for old block
				screenColliders[i][j] = false;

				//set screen collider for new block
				screenColliders[i + 1][j] = true;
			}
		}
	}
}

void App::clearLine(int yIndex) {
	for (int i = 0; i < SCREEN_WIDTH / 32 - 6; i++)
	{
		screenBlocks[yIndex][i] = NULL;
	}
}

bool App::checkLineCleared(int yIndex) {
	//check if line y is cleared
	for (int j = 0; j < SCREEN_WIDTH / 32 - 6; j++)
	{
		if (screenColliders[yIndex][j] == false)
			return false;
	}

	return true;
}

bool App::checkBlockOutOfScreen(Block* blocks) {
	for (int i = 0; i < 4; i++)
	{
		if (blocks[i].getXPos() < 0 || blocks[i].getXPos() + blocks[i].getWidth() > SCREEN_WIDTH - BLOCK_WIDTH * 6 || blocks[i].getYPos() + blocks[i].getHeight() > SCREEN_HEIGHT)
			return true;
	}

	return false;
}

bool App::checkCollision(Block* blocks, bool** screenColliders) {
	//arrays to store indexes of blocks
	int xIndexes[4] = { blocks[0].getXPos() / 32, blocks[1].getXPos() / 32, blocks[2].getXPos() / 32, blocks[3].getXPos() / 32 };
	int yIndexes[4] = { blocks[0].getYPos() / 32, blocks[1].getYPos() / 32, blocks[2].getYPos() / 32, blocks[3].getYPos() / 32 };

	//check if there is a screen collider at x, y indexes
	for (int i = 0; i < 4; i++)
	{
		if (screenColliders[yIndexes[i]][xIndexes[i]] == true)
			return true;
	}

	return false;
}

void App::close() {
	delete [] screenColliders;

	//destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	gTextTexture = NULL;
	gLevelTextTexture = NULL;
	gLevelTexture = NULL;
	gScoreTexture = NULL;

	//Quit SDL subsystems
	//IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

bool App::loadMedia()
{
    //Loading success flag
    bool success = true;

    //Open the font
    gFont = TTF_OpenFont( "02_getting_an_image_on_the_screen/kingrich.ttf", 28 );

    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //initialize score text
        SDL_Color textColor = { 0, 0, 0 };

        if( !gTextTexture->loadFromRenderedText(gRenderer, gFont, "Score", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }

        if( !gScoreTexture->loadFromRenderedText(gRenderer, gFont, "0", textColor ) )
        {
            printf( "Failed to render score texture!\n" );
            success = false;
        }

        //initialize level text
        if( !gLevelTextTexture->loadFromRenderedText(gRenderer, gFont, "Level", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }

        //initialize level
        if( !gLevelTexture->loadFromRenderedText(gRenderer, gFont, "1", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }

        //initialize lines text
        if( !gLinesTextTexture->loadFromRenderedText(gRenderer, gFont, "Lines", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }

        //initialize lines
        if( !gLinesTexture->loadFromRenderedText(gRenderer, gFont, "0", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }

    return success;
}