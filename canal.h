#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class canal
{
public:
	SDL_Texture *canal1up = NULL;
	SDL_Texture *canal2up = NULL;
	SDL_Texture *canal3up = NULL;
	SDL_Texture *canal4up = NULL;
	SDL_Texture *canal1dw = NULL;
	SDL_Texture *canal2dw = NULL;
	SDL_Texture *canal3dw = NULL;
	SDL_Texture *canal4dw = NULL;
	SDL_Rect canal1rup = {760, -30, 152, 460};
	SDL_Rect canal2rup = {760, -30, 152, 120};
	SDL_Rect canal3rup = {760, -30, 152, 400};
	SDL_Rect canal4rup = {760, -30, 152, 300};
	//Down Canals Rects
	SDL_Rect canal1rdw = {760, 630, 152, 25};
	SDL_Rect canal2rdw = {760, 290, 152, 365};
	SDL_Rect canal3rdw = {760, 570, 152, 85};
	SDL_Rect canal4rdw = {760, 470, 152, 185};
	SDL_Surface *Canal_Surface = NULL;
} ca;