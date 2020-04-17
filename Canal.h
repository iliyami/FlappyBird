#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

class Canal
{
public:
    //Every Rect has a x, y, w, h
    //Up Canals Rects
    SDL_Rect canal1rup = {760, -30, 152, 460};
    SDL_Rect canal2rup = {760, -30, 152, 120};
    SDL_Rect canal3rup = {760, -30, 152, 400};
    SDL_Rect canal4rup = {760, -30, 152, 300};
    //Down Canals Rects
    SDL_Rect canal1rdw = {760, 630, 152, 25};
    SDL_Rect canal2rdw = {760, 290, 152, 365};
    SDL_Rect canal3rdw = {760, 570, 152, 85};
    SDL_Rect canal4rdw = {760, 470, 152, 185};

    void canal_move(int &, int &, int &, bool &, bool &, SDL_Rect &, Mix_Chunk *);
};

void Canal::canal_move(int &cn, int &canalnum, int &POINTS, bool &endcanal1, bool &Gameover, SDL_Rect &grect1, Mix_Chunk *Point)
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
			if (canal1rup.x == grect1.x - 150 && Gameover == false)
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
			if (canal2rup.x == grect1.x - 150 && Gameover == false)
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
			if ( canal3rup.x == grect1.x - 150 && Gameover == false)
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
			if (canal4rup.x == grect1.x - 150 && Gameover == false)
			{
				POINTS++;
				Mix_PlayChannel(-1, Point, 0);
			}
			break;
		}
		}
	}
}
