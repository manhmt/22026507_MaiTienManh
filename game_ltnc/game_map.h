#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "BaseObject.h"
#include "CommonFunc.h"

#define MAX_TILE 20

class TileMat : public BaseObject
{
public:
	TileMat() { ; }
	~TileMat() { ; }
};

class GameMap
{
public:
	GameMap();
	~GameMap();
	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map getMap() const { return game_map_; };
	void setMap(Map& map_data) { game_map_ = map_data; };
	SDL_Point ToScreenCoordinates(int map_x, int map_y, const Map& map_data);

private:
	Map game_map_;
	TileMat tile_mat[MAX_TILE];
};
#endif