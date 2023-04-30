#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <windows.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int FRAME_PER_SECOND = 40;
//Screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

//Color key
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0Xff;

//TILE
#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define STATE_MONEY 4
struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
};
struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	std::string file_name_;
};

namespace SDLCommonFunc
{
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}
#endif
