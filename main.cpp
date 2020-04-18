#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_mixer.h>
#include "Bird.h"
#include "canal.h"

using namespace std;

bool run;
bool Gameover;
int POINTS = 0;
bool loadendemage = false;
bool StartGame = true;
int cn = 0;	 //use for random canals
int cn2 = 0; //use for random day and night

const int SCREEN_WIDTH = 760;
const int SCREEN_HEIGHT = 800;
//renderer
SDL_Renderer *gRenderer = NULL;

//textures
SDL_Texture *gTexture1 = NULL;
//for GameOver BMP
SDL_Texture *gTexture2 = NULL;
SDL_Texture *gbackgroundT = NULL;

//canal textures in canal.h

SDL_Texture *S1 = NULL;
SDL_Texture *S2 = NULL;
SDL_Texture *S3 = NULL;
SDL_Texture *S4 = NULL;
SDL_Texture *S5 = NULL;
SDL_Texture *S6 = NULL;
SDL_Texture *S7 = NULL;
SDL_Texture *S8 = NULL;
SDL_Texture *S9 = NULL;
SDL_Texture *S0 = NULL;

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

//rects:
//bird1
SDL_Rect grect1;
//Baclground Rects
SDL_Rect backrect = {0, 0, 2280, 800};
//Up Canals Rects

//GameOver Rect
SDL_Rect GO = {80, 130, 500, 500};
//Points(Scores) Rect
SDL_Rect score1 = {0, 0, 40, 50};
SDL_Rect score2 = {50, 0, 40, 50};

//Surface for loading png images (except map)
SDL_Surface *gSurface1 = NULL; //bird1
SDL_Surface *canalsurface = NULL;
SDL_Surface *background = NULL;

//keyboard states
const Uint8 *state = SDL_GetKeyboardState(NULL);

//Sounds:
//Main music
Mix_Music *gMusic = NULL;
//Lose sound
Mix_Chunk *Lose_sound = NULL;
//Point sound
Mix_Chunk *Point = NULL;

bool init()
{

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Fat Bird", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		//Initialise SDL_mixer and Music
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}
		gMusic = Mix_LoadMUS("Media/Martik_Parandeh.wav");
		Lose_sound = Mix_LoadWAV("Media/hit.wav");
		Point = Mix_LoadWAV("Media/point.wav");

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			if (cn2 == 1)
			{
				gSurface1 = SDL_LoadBMP("Media/bird11.bmp");
			}
			if (cn2 == 2)
			{
				gSurface1 = SDL_LoadBMP("Media/Bird2.bmp");
			}
			gTexture1 = SDL_CreateTextureFromSurface(gRenderer, gSurface1);

			ca.Canal_Surface = SDL_LoadBMP("Media/canal1up.bmp");
			ca.canal1up = SDL_CreateTextureFromSurface(gRenderer, ca.Canal_Surface);

			ca.Canal_Surface = SDL_LoadBMP("Media/canal2up.bmp");
			ca.canal2up = SDL_CreateTextureFromSurface(gRenderer, ca.Canal_Surface);

			ca.Canal_Surface = SDL_LoadBMP("Media/canal3up.bmp");
			ca.canal3up = SDL_CreateTextureFromSurface(gRenderer, ca.Canal_Surface);

			ca.Canal_Surface = SDL_LoadBMP("Media/canal4up.bmp");
			ca.canal4up = SDL_CreateTextureFromSurface(gRenderer, ca.Canal_Surface);

			ca.Canal_Surface = SDL_LoadBMP("Media/canal1dw.bmp");
			ca.canal1dw = SDL_CreateTextureFromSurface(gRenderer, ca.Canal_Surface);

			ca.Canal_Surface = SDL_LoadBMP("Media/canal2dw.bmp");
			ca.canal2dw = SDL_CreateTextureFromSurface(gRenderer, ca.Canal_Surface);

			ca.Canal_Surface = SDL_LoadBMP("Media/canal3dw.bmp");
			ca.canal3dw = SDL_CreateTextureFromSurface(gRenderer, ca.Canal_Surface);

			ca.Canal_Surface = SDL_LoadBMP("Media/canal4dw.bmp");
			ca.canal4dw = SDL_CreateTextureFromSurface(gRenderer, ca.Canal_Surface);

			//Scores media
			S0 = IMG_LoadTexture(gRenderer, "Numbers/0.png");
			S1 = IMG_LoadTexture(gRenderer, "Numbers/1.png");
			S2 = IMG_LoadTexture(gRenderer, "Numbers/2.png");
			S3 = IMG_LoadTexture(gRenderer, "Numbers/3.png");
			S4 = IMG_LoadTexture(gRenderer, "Numbers/4.png");
			S5 = IMG_LoadTexture(gRenderer, "Numbers/5.png");
			S6 = IMG_LoadTexture(gRenderer, "Numbers/6.png");
			S7 = IMG_LoadTexture(gRenderer, "Numbers/7.png");
			S8 = IMG_LoadTexture(gRenderer, "Numbers/8.png");
			S9 = IMG_LoadTexture(gRenderer, "Numbers/9.png");

			bird1.x = 340;
			bird1.y = 360;
			grect1.x = bird1.x;
			grect1.y = bird1.y;
		}
	}

	return success;
}

void loadMedia()
{
	//Load random image
	if (cn2 == 1)
	{
		background = SDL_LoadBMP("Media/daybackground1.bmp");
	}
	if (cn2 == 2)
	{
		background = SDL_LoadBMP("Media/daybackground2.bmp");
	}

	gbackgroundT = SDL_CreateTextureFromSurface(gRenderer, background);
}

bool checkcollision()
{
	if (Gameover == false)
	{
		if (SDL_HasIntersection(&grect1, &ca.canal1rup) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &ca.canal1rdw) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &ca.canal2rup) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &ca.canal2rdw) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &ca.canal3rup) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &ca.canal3rdw) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &ca.canal4rup) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &ca.canal4rdw) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}

		//up wall
		if (grect1.y < 0)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		//ground
		if (grect1.y > 600)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}

		return true;
	}
	return false;
}

bool start = false;
bool movebird(SDL_Event e, bool *quit)
{
	if (start)
	{

		if (bird1.speed > -0.4)
		{
			bird1.speed -= bird1.acc;
		}

		SDL_PollEvent(&e);
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
		{
			bird1.speed += 1.3;
		}

		bird1.y -= bird1.speed;

		if (e.type == SDL_QUIT)
		{
			*quit = true;
		}
	}
	else
	{
		SDL_PollEvent(&e);
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
		{
			start = true;
			bird1.speed += 0.9;
		}
		if (e.type == SDL_QUIT)
		{
			*quit = true;
		}
	}

	grect1 = {bird1.x, bird1.y, 60, 60};
	return checkcollision();
}

void Points()
{
	switch (POINTS)
	{
	case 0:
		SDL_RenderCopy(gRenderer, S0, NULL, &score1);
		break;
	case 1:
		SDL_RenderCopy(gRenderer, S1, NULL, &score1);
		break;
	case 2:
		SDL_RenderCopy(gRenderer, S2, NULL, &score1);
		break;
	case 3:
		SDL_RenderCopy(gRenderer, S3, NULL, &score1);
		break;
	case 4:
		SDL_RenderCopy(gRenderer, S4, NULL, &score1);
		break;
	case 5:
		SDL_RenderCopy(gRenderer, S5, NULL, &score1);
		break;
	case 6:
		SDL_RenderCopy(gRenderer, S6, NULL, &score1);
		break;
	case 7:
		SDL_RenderCopy(gRenderer, S7, NULL, &score1);
		break;
	case 8:
		SDL_RenderCopy(gRenderer, S8, NULL, &score1);
		break;
	case 9:
		SDL_RenderCopy(gRenderer, S9, NULL, &score1);
		break;
	case 10:
		SDL_RenderCopy(gRenderer, S1, NULL, &score1);
		SDL_RenderCopy(gRenderer, S0, NULL, &score2);
		break;
	case 11:
		SDL_RenderCopy(gRenderer, S1, NULL, &score1);
		SDL_RenderCopy(gRenderer, S1, NULL, &score2);
		break;
	case 12:
		SDL_RenderCopy(gRenderer, S1, NULL, &score1);
		SDL_RenderCopy(gRenderer, S2, NULL, &score2);
		break;
	case 13:
		SDL_RenderCopy(gRenderer, S1, NULL, &score1);
		SDL_RenderCopy(gRenderer, S3, NULL, &score2);
		break;
	case 14:
		SDL_RenderCopy(gRenderer, S1, NULL, &score1);
		SDL_RenderCopy(gRenderer, S4, NULL, &score2);
		break;
	case 15:
		SDL_RenderCopy(gRenderer, S1, NULL, &score1);
		SDL_RenderCopy(gRenderer, S5, NULL, &score2);
		break;
	case 16:
		SDL_RenderCopy(gRenderer, S1, NULL, &score1);
		SDL_RenderCopy(gRenderer, S6, NULL, &score2);
		break;
	case 17:
		SDL_RenderCopy(gRenderer, S1, NULL, &score1);
		SDL_RenderCopy(gRenderer, S7, NULL, &score2);
		break;
	case 18:
		SDL_RenderCopy(gRenderer, S1, NULL, &score1);
		SDL_RenderCopy(gRenderer, S8, NULL, &score2);
		break;
	case 19:
		SDL_RenderCopy(gRenderer, S1, NULL, &score1);
		SDL_RenderCopy(gRenderer, S9, NULL, &score2);
		break;
	case 20:
		SDL_RenderCopy(gRenderer, S2, NULL, &score1);
		SDL_RenderCopy(gRenderer, S0, NULL, &score2);
		break;
	}
}

bool endcanal1 = false;
bool endcanal2 = false; //ezaf
int canalnum = 0;

void canal_move()
{
	float speed = 1;
	if (cn == 1 && !endcanal1)
	{

		endcanal1 = true;
		canalnum = 1;
	}
	if (cn == 2 && !endcanal1)
	{

		endcanal1 = true;
		canalnum = 2;
	}
	if (cn == 3 && !endcanal1)
	{

		endcanal1 = true;
		canalnum = 3;
	}
	if (cn == 4 && !endcanal1)
	{

		endcanal1 = true;
		canalnum = 4;
	}
	if (endcanal1)
	{
		switch (canalnum)
		{
		case 1:
		{
			ca.canal1rdw.x -= speed;
			ca.canal1rup.x -= speed;
			if (ca.canal1rup.x < -152)
			{
				ca.canal1rup.x = 760;
				ca.canal1rdw.x = 760;
				endcanal1 = false;
			}
			if (ca.canal1rup.x == grect1.x - 150)
			{
				POINTS++;
				Mix_PlayChannel(-1, Point, 0);
			}

			break;
		}

		case 2:
		{
			ca.canal2rdw.x -= speed;
			ca.canal2rup.x -= speed;
			if (ca.canal2rup.x < -152)
			{
				ca.canal2rup.x = 760;
				ca.canal2rdw.x = 760;
				endcanal1 = false;
			}
			if (ca.canal2rup.x == grect1.x - 150)
			{
				POINTS++;
				Mix_PlayChannel(-1, Point, 0);
			}
			break;
		}

		case 3:
		{
			ca.canal3rdw.x -= speed;
			ca.canal3rup.x -= speed;
			if (ca.canal3rup.x < -152)
			{
				ca.canal3rup.x = 760;
				ca.canal3rdw.x = 760;
				endcanal1 = false;
			}
			if (ca.canal3rup.x == grect1.x - 150)
			{
				POINTS++;
				Mix_PlayChannel(-1, Point, 0);
			}
			break;
		}

		case 4:
		{
			ca.canal4rdw.x -= speed;
			ca.canal4rup.x -= speed;
			if (ca.canal4rup.x < -152)
			{
				ca.canal4rup.x = 760;
				ca.canal4rdw.x = 760;
				endcanal1 = false;
			}
			if (ca.canal4rup.x == grect1.x - 150)
			{
				POINTS++;
				Mix_PlayChannel(-1, Point, 0);
			}
			break;
		}
		}
	}
}

void setcn()
{
	cn = rand() % 4 + 1;
}
void setcn2()
{
	cn2 = rand() % 2 + 1;
}

void GameOver(SDL_Event e, bool *quit)
{

	GO.h = 450;
	GO.w = 600;
	POINTS = 0;
	Gameover = true;
	// StartGame = false;
	gSurface1 = SDL_LoadBMP("Media/GO.bmp");
	if (loadendemage == false)
	{
		gTexture2 = SDL_CreateTextureFromSurface(gRenderer, gSurface1);

		loadendemage = true;
	}
	SDL_FreeSurface(gSurface1);
	SDL_DestroyTexture(gTexture1);

	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT)
	{
		*quit = true;
	}
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
	{
		start = false;
		SDL_DestroyTexture(gTexture2);
		GO.h = 0;
		GO.w = 0;
		Gameover = false;
		if (cn2 == 1)
		{
			gSurface1 = SDL_LoadBMP("Media/bird11.bmp");
		}
		if (cn2 == 2)
		{
			gSurface1 = SDL_LoadBMP("Media/Bird2.bmp");
		}

		Mix_PlayMusic(gMusic, -1);
		bird1.x = 340;
		bird1.y = 360;
		grect1.x = bird1.x;
		grect1.y = bird1.y;
		switch (canalnum)
		{
		case 1:
		{

			ca.canal1rup.x = 760;
			ca.canal1rdw.x = 760;
			break;
		}

		case 2:
		{

			ca.canal2rup.x = 760;
			ca.canal2rdw.x = 760;

			break;
		}

		case 3:
		{
			ca.canal3rup.x = 760;
			ca.canal3rdw.x = 760;
			break;
		}

		case 4:
		{
			ca.canal4rup.x = 760;
			ca.canal4rdw.x = 760;
			break;
		}
		}
		gTexture1 = SDL_CreateTextureFromSurface(gRenderer, gSurface1);
		loadendemage = false;
	}
}

int main()
{
	loadendemage = false;
	run = true;
	srand(time(0));
	setcn2();

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//For closing the program

		bool *quit = new bool;
		*quit = false;
		SDL_Event e;

		//Load media
		while (!*quit && StartGame) //you can add a condition for run game again by menu in this while !!!!!!!!!!
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					*quit = true;
				}
			}
			loadMedia();
			Gameover = false;
			//Playing the main music
			Mix_PlayMusic(gMusic, -1);

			int b = 0; //for move ment of back ground
			do
			{
				SDL_RenderCopy(gRenderer, gbackgroundT, NULL, &backrect);
				SDL_RenderCopy(gRenderer, ca.canal1up, NULL, &ca.canal1rup);
				SDL_RenderCopy(gRenderer, ca.canal2up, NULL, &ca.canal2rup);
				SDL_RenderCopy(gRenderer, ca.canal3up, NULL, &ca.canal3rup);
				SDL_RenderCopy(gRenderer, ca.canal4up, NULL, &ca.canal4rup);
				SDL_RenderCopy(gRenderer, ca.canal1dw, NULL, &ca.canal1rdw);
				SDL_RenderCopy(gRenderer, ca.canal2dw, NULL, &ca.canal2rdw);
				SDL_RenderCopy(gRenderer, ca.canal3dw, NULL, &ca.canal3rdw);
				SDL_RenderCopy(gRenderer, ca.canal4dw, NULL, &ca.canal4rdw);
				SDL_RenderCopy(gRenderer, gTexture2, NULL, &GO);
				Points();

				//movement of back ground
				b++;
				if (b == 10)
				{
					backrect.x -= 1;
					if (start)
						canal_move(); //move canals
					setcn();

					b = 0;
				}
				if (POINTS == 20)
				{
					*quit = true;
				}
				if (backrect.x < -1520)
				{
					backrect.x = 0;
				}
				//end of movement of back ground

				SDL_RenderCopy(gRenderer, gTexture1, NULL, &grect1);
				SDL_RenderPresent(gRenderer);
				if (movebird(e, quit) == false)
				{
					GameOver(e, quit);
				}
			} while (!*quit);

			run = false;
		}
	}
}