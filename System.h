#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_mixer.h>
#include "Bird.h"

using namespace std;

class System
{
public:
    bool run;
    bool Gameover;
    int POINTS = 0;
    bool loadendemage = false;
    bool StartGame = true;
    int cn=0;//use for random canals
    int cn2=0;//use for random day and night
    bool start = false;
    bool endcanal1=false;
    bool endcanal2=false;//ezaf
    int canalnum=0;
    const int SCREEN_WIDTH = 760;
    const int SCREEN_HEIGHT = 800;
    //renderer
    SDL_Renderer *gRenderer = NULL;
    //textures
    SDL_Texture *gTexture1 = NULL;
    //for GameOver BMP
    SDL_Texture *gTexture2 = NULL;
    SDL_Texture *gbackgroundT = NULL;
    SDL_Texture *canal1up = NULL;
    SDL_Texture *canal2up = NULL;
    SDL_Texture *canal3up = NULL;
    SDL_Texture *canal4up = NULL;
    SDL_Texture *canal1dw = NULL;
    SDL_Texture *canal2dw = NULL;
    SDL_Texture *canal3dw = NULL;
    SDL_Texture *canal4dw = NULL;
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
    SDL_Window* gWindow = NULL;

    //The surface contained by the window
    SDL_Surface *gScreenSurface = NULL;
    SDL_Surface *Canal_Surface = NULL;
    //Surface for loading png images (except map)
    //bird1
    SDL_Surface *gSurface1 = NULL;
    //canal's surface
    SDL_Surface *canalsurface = NULL;
    //Background's surface
    SDL_Surface *background = NULL;

    //rects:
    //bird1
    SDL_Rect grect1;
    //Baclground Rects
    SDL_Rect backrect;
    //Up Canals Rects
    SDL_Rect canal1rup;
    SDL_Rect canal2rup;
    SDL_Rect canal3rup;
    SDL_Rect canal4rup;
    //Down Canals Rects
    SDL_Rect canal1rdw;
    SDL_Rect canal2rdw;
    SDL_Rect canal3rdw;
    SDL_Rect canal4rdw;
    //GameOver Rect
    SDL_Rect GO;
    //Points(Scores) Rect
    SDL_Rect score1;
    SDL_Rect score2;
    //keyboard states
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    //Sounds:
    //Main music
    Mix_Music *gMusic = NULL;
    //Lose sound
    Mix_Chunk *Lose_sound = NULL;
    //Point sound
    Mix_Chunk *Point = NULL;

    void initialize_Bird_pics();
    void initialize_Canal_pics();
    void initialize_Rects();
    // void initialize_grenderer();
    void initialize_Sounds();
    void initialize_Score_pics();
    bool init();
    void loadMedia();
    bool checkcollision();
    bool movebird(SDL_Event e, bool *quit);
    void Points();
    void canal_move();
    void setcn();
    void setcn2();
    void GameOver(SDL_Event , bool *);
    void GameLoop();

};
void System::initialize_Bird_pics()
{
    if (cn2 == 1)
    {
        gSurface1 = SDL_LoadBMP("Media/bird11.bmp");
    }
    if (cn2 == 2)
    {
        gSurface1 = SDL_LoadBMP("Media/Bird2.bmp");
    }
    gTexture1 = SDL_CreateTextureFromSurface(gRenderer, gSurface1);
}
void System::initialize_Canal_pics()
{
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
}
void System::initialize_Rects()
{
    SDL_Rect grect1;
    SDL_Rect backrect = {0, 0, 2280, 800};
    SDL_Rect canal1rup = {760, -30, 152, 460};
    SDL_Rect canal2rup = {760, -30, 152, 120};
    SDL_Rect canal3rup = {760, -30, 152, 400};
    SDL_Rect canal4rup = {760, -30, 152, 300};
    SDL_Rect canal1rdw = {760, 630, 152, 25};
    SDL_Rect canal2rdw = {760, 290, 152, 365};
    SDL_Rect canal3rdw = {760, 570, 152, 85};
    SDL_Rect canal4rdw = {760, 470, 152, 185};
    SDL_Rect GO = {80, 130, 500, 500};
    SDL_Rect score1 = {0, 0, 40, 50};
    SDL_Rect score2 = {50, 0, 40, 50};
}

void System::initialize_Sounds()
{
    gMusic = Mix_LoadMUS("Media/Martik_Parandeh.wav");
    Lose_sound = Mix_LoadWAV("Media/hit.wav");
    Point = Mix_LoadWAV("Media/point.wav");
}
void System::initialize_Score_pics()
{
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
}

bool System::init()
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
		
        initialize_Sounds();
		
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			initialize_Bird_pics();

			initialize_Canal_pics();

            initialize_Score_pics();

            bird1.set_bird(340, 360);
			
			grect1.x = bird1.x;
			grect1.y = bird1.y;
		}
	}

	return success;
}

void System::loadMedia()
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

bool System::checkcollision()
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

bool System::movebird(SDL_Event e, bool *quit)
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

void System::Points()
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

void System::canal_move()
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
			if (canal1rup.x == grect1.x - 150)
			{
				POINTS++;
				Mix_PlayChannel(-1, Point, 0);
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
			if (canal2rup.x == grect1.x - 150)
			{
				POINTS++;
				Mix_PlayChannel(-1, Point, 0);
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
			if ( canal3rup.x == grect1.x - 150)
			{
				POINTS++;
				Mix_PlayChannel(-1, Point, 0);
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
			if (canal4rup.x == grect1.x - 150)
			{
				POINTS++;
				Mix_PlayChannel(-1, Point, 0);
			}
			break;
		}
		}
	}
}

void System::setcn()
{
	cn = rand() % 4 + 1;
}
void System::setcn2()
{
	cn2 = rand() % 2 + 1;
}

void System::GameOver(SDL_Event e, bool *quit)
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
		loadendemage=false;
	}
}

void System::GameLoop()
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

#endif