#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Bird.h"
#include "Canal.h"

using namespace std;

bool run;
bool Gameover;
int POINTS = 0;
bool loadendemage=false;
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
SDL_Texture* S1= NULL;
SDL_Texture* S2= NULL;
SDL_Texture* S3= NULL;
SDL_Texture* S4= NULL;
SDL_Texture* S5= NULL;
SDL_Texture* S6= NULL;
SDL_Texture* S7= NULL;
SDL_Texture* S8= NULL;
SDL_Texture* S9= NULL;
SDL_Texture* S0= NULL;


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

//GameOver Rect
SDL_Rect GO={80,130,500,500};
//Points(Scores) Rect
SDL_Rect score1={0,0,40,50};
SDL_Rect score2={50,0,40,50};

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

bool checkcollision(Canal &canal)
{
	if (Gameover == false)
	{
		if (SDL_HasIntersection(&grect1, &canal.canal1rup) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &canal.canal1rdw) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &canal.canal2rup) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &canal.canal2rdw) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &canal.canal3rup) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &canal.canal3rdw) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &canal.canal4rup) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		if (SDL_HasIntersection(&grect1, &canal.canal4rdw) == true)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}

		//up wall
		if (grect1.y<0)
		{
			bird1.lose = true;
			Mix_PlayChannel(-1, Lose_sound, 0);
			return false;
		}
		//ground
		if (grect1.y>600)
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
bool movebird(SDL_Event e, bool *quit, Canal &canal)
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
	return checkcollision(canal);
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

bool endcanal1=false;
bool endcanal2=false;//ezaf
int canalnum=0;

void setcn()
{
	cn = rand() % 4 + 1;
}
void setcn2()
{
	cn2 = rand() % 2 + 1;
}

void GameOver(SDL_Event e, bool *quit, Canal canal)
{
	
	GO.h = 450;
	GO.w = 600;
	POINTS = 0;
	Gameover = true;
	// StartGame = false;
	gSurface1 = SDL_LoadBMP("Media/GO.bmp");
	if(loadendemage==false)
	{
	gTexture2 = SDL_CreateTextureFromSurface(gRenderer, gSurface1);
	
	loadendemage=true;
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
		start=false;
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

			canal.canal1rup.x = 760;
			canal.canal1rdw.x = 760;
			break;
		}

		case 2:
		{

			canal.canal2rup.x = 760;
			canal.canal2rdw.x = 760;

			break;
		}

		case 3:
		{
			canal.canal3rup.x = 760;
			canal.canal3rdw.x = 760;
			break;
		}

		case 4:
		{
			canal.canal4rup.x = 760;
			canal.canal4rdw.x = 760;
			break;
		}
		}
		loadendemage=false;
	}
}

int main()
{
	Canal canal;
	loadendemage=false;
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
				SDL_RenderCopy(gRenderer, canal1up, NULL, &canal.canal1rup);
				SDL_RenderCopy(gRenderer, canal2up, NULL, &canal.canal2rup);
				SDL_RenderCopy(gRenderer, canal3up, NULL, &canal.canal3rup);
				SDL_RenderCopy(gRenderer, canal4up, NULL, &canal.canal4rup);
				SDL_RenderCopy(gRenderer, canal1dw, NULL, &canal.canal1rdw);
				SDL_RenderCopy(gRenderer, canal2dw, NULL, &canal.canal2rdw);
				SDL_RenderCopy(gRenderer, canal3dw, NULL, &canal.canal3rdw);
				SDL_RenderCopy(gRenderer, canal4dw, NULL, &canal.canal4rdw);
				SDL_RenderCopy(gRenderer, gTexture2, NULL, &GO);
				Points();

				//movement of back ground
				b++;
				if (b == 10)
				{
					backrect.x -= 1;
					if(start)
					canal.canal_move(cn,canalnum,POINTS,endcanal1,Gameover,grect1, Point); //move canals
					setcn();

					b = 0;
				}

				if (backrect.x < -1520)
				{
					backrect.x = 0;
				}

				if (POINTS == 20)
				{
					SDL_Quit();
				}
				

				//end of movement of back ground
				SDL_RenderCopy(gRenderer, gTexture1, NULL, &grect1);
				SDL_RenderPresent(gRenderer);
				if (movebird(e, quit, canal) == false)
				{			
					GameOver(e,quit,canal);
				}
			} while (!*quit);

			run = false;
		}
	}
}