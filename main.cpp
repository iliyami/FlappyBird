#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_mixer.h>
#include "Bird.h"

using namespace std;


bool run;
bool Gameover;
bool StartGame = true;
int cn=0;//use for random canals
int cn2=0;//use for random day and night

const int SCREEN_WIDTH = 760;
const int SCREEN_HEIGHT = 800;
//renderer
SDL_Renderer *gRenderer = NULL;


//textures
SDL_Texture* gTexture1 = NULL;
//for GameOver BMP
SDL_Texture* gTexture2 = NULL;
SDL_Texture* gbackgroundT = NULL;
SDL_Texture* canal1up= NULL;
SDL_Texture* canal2up= NULL;
SDL_Texture* canal3up= NULL;
SDL_Texture* canal4up= NULL;
SDL_Texture* canal1dw= NULL;
SDL_Texture* canal2dw= NULL;
SDL_Texture* canal3dw= NULL;
SDL_Texture* canal4dw= NULL;


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* Canal_Surface = NULL;

//rects:
//bird1
SDL_Rect grect1;
//Baclground Rects
SDL_Rect backrect={0,0,2280,800};
//Up Canals Rects
SDL_Rect canal1rup={760,0,152,460};
SDL_Rect canal2rup={760,0,152,120};
SDL_Rect canal3rup={760,0,152,400};
SDL_Rect canal4rup={760,0,152,300};
//Down Canals Rects
SDL_Rect canal1rdw={760,630,152,25};
SDL_Rect canal2rdw={760,290,152,365};
SDL_Rect canal3rdw={760,570,152,85};
SDL_Rect canal4rdw={760,470,152,185};
//GameOver Rect
SDL_Rect GO={0,0,500,500};



//Surface for loading png images (except map)
SDL_Surface* gSurface1 = NULL; //bird1
SDL_Surface* canalsurface= NULL;
SDL_Surface* background=NULL;

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
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Fat Bird", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
		
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			if(cn2==1)
			{
				gSurface1 = SDL_LoadBMP("Media/bird11.bmp");
			}
			if(cn2==2)
			{
				gSurface1 = SDL_LoadBMP("Media/Bird2.bmp");
			}
			gTexture1 = SDL_CreateTextureFromSurface(gRenderer, gSurface1);

			Canal_Surface = SDL_LoadBMP("Media/canal1up.bmp");
			canal1up = SDL_CreateTextureFromSurface(gRenderer, Canal_Surface);

			Canal_Surface = SDL_LoadBMP("Media/canal2up.bmp");
			canal2up = SDL_CreateTextureFromSurface(gRenderer, Canal_Surface);

			Canal_Surface = SDL_LoadBMP("Media/canal3up.bmp");
			canal3up = SDL_CreateTextureFromSurface(gRenderer, Canal_Surface);

			Canal_Surface = SDL_LoadBMP("Media/canal4up.bmp");
			canal4up = SDL_CreateTextureFromSurface(gRenderer, Canal_Surface);

			Canal_Surface = SDL_LoadBMP("Media/canal1dw.bmp");
			canal1dw = SDL_CreateTextureFromSurface(gRenderer, Canal_Surface);

			Canal_Surface = SDL_LoadBMP("Media/canal2dw.bmp");
			canal2dw = SDL_CreateTextureFromSurface(gRenderer, Canal_Surface);

			Canal_Surface = SDL_LoadBMP("Media/canal3dw.bmp");
			canal3dw = SDL_CreateTextureFromSurface(gRenderer, Canal_Surface);

			Canal_Surface = SDL_LoadBMP("Media/canal4dw.bmp");
			canal4dw = SDL_CreateTextureFromSurface(gRenderer, Canal_Surface);

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
	if(cn2==1)
	{
		background = SDL_LoadBMP("Media/daybackground1.bmp");
	}
	if(cn2==2)
	{
		background = SDL_LoadBMP("Media/daybackground2.bmp");
	}
  			
   	gbackgroundT = SDL_CreateTextureFromSurface(gRenderer, background);
}

bool checkcollision()
{
	if (Gameover == false)
	{
		if (SDL_HasIntersection(&grect1, &canal1rup) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &canal1rdw) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &canal2rup) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &canal2rdw) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &canal3rup) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &canal3rdw) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &canal4rup) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &canal4rdw) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}

		return true;
	}
	
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
	}

	grect1 = {bird1.x, bird1.y, 60, 60};
	return checkcollision();
}

bool endcanal1=false;
bool endcanal2=false;//ezaf
int canalnum=0;

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
			canal1rdw.x -= speed;
			canal1rup.x -= speed;
			if (canal1rup.x < -152)
			{
				canal1rup.x = 760;
				canal1rdw.x = 760;
				endcanal1 = false;
			}

			break;
		}

		case 2:
		{
			canal2rdw.x -= speed;
			canal2rup.x -= speed;
			if (canal2rup.x < -152)
			{
				canal2rup.x = 760;
				canal2rdw.x = 760;
				endcanal1 = false;
			}

			break;
		}

		case 3:
		{
			canal3rdw.x -= speed;
			canal3rup.x -= speed;
			if (canal3rup.x < -152)
			{
				canal3rup.x = 760;
				canal3rdw.x = 760;
				endcanal1 = false;
			}

			break;
		}

		case 4:
		{
			canal4rdw.x -= speed;
			canal4rup.x -= speed;
			if (canal4rup.x < -152)
			{
				canal4rup.x = 760;
				canal4rdw.x = 760;
				endcanal1 = false;
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

void GameOver(SDL_Event e)
{
	Gameover = true;
	GO.h = 500;
	GO.w = 500;
	// StartGame = false;
	SDL_FreeSurface(gSurface1);
	SDL_DestroyTexture(gTexture1);
	gSurface1 = SDL_LoadBMP("Media/GO.bmp");
	gTexture2 = SDL_CreateTextureFromSurface(gRenderer, gSurface1);
	SDL_PollEvent(&e);
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
	{
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
		gTexture1 = SDL_CreateTextureFromSurface(gRenderer, gSurface1);
		Mix_PlayMusic(gMusic, -1);
		bird1.x = 340;
    	bird1.y = 360;
		grect1.x = bird1.x;
		grect1.y = bird1.y;
		switch (canalnum)
		{
		case 1:
		{

			canal1rup.x = 760;
			canal1rdw.x = 760;
			break;
		}

		case 2:
		{

			canal2rup.x = 760;
			canal2rdw.x = 760;

			break;
		}

		case 3:
		{
			canal3rup.x = 760;
			canal3rdw.x = 760;
			break;
		}

		case 4:
		{
			canal4rup.x = 760;
			canal4rdw.x = 760;
			break;
		}
		}
	}
}

int main()
{
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
				//grect1 = {bird1.x , bird1.y , 60, 60};
				SDL_RenderCopy(gRenderer, gbackgroundT, NULL, &backrect);
				SDL_RenderCopy(gRenderer, canal1up, NULL, &canal1rup);
				SDL_RenderCopy(gRenderer, canal2up, NULL, &canal2rup);
				SDL_RenderCopy(gRenderer, canal3up, NULL, &canal3rup);
				SDL_RenderCopy(gRenderer, canal4up, NULL, &canal4rup);
				SDL_RenderCopy(gRenderer, canal1dw, NULL, &canal1rdw);
				SDL_RenderCopy(gRenderer, canal2dw, NULL, &canal2rdw);
				SDL_RenderCopy(gRenderer, canal3dw, NULL, &canal3rdw);
				SDL_RenderCopy(gRenderer, canal4dw, NULL, &canal4rdw);
				SDL_RenderCopy(gRenderer, gTexture2, NULL, &GO);

				//movement of back ground
				b++;
				if (b == 10)
				{
					backrect.x -= 1;
					canal_move(); //move canals
					setcn();

					b = 0;
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
					GameOver(e);
				}
			} while (!*quit);

			run = false;
		}
	}
}