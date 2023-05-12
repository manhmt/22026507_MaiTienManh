#ifndef GAME_H_
#define GAME_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "PlayerPower.h"
//#include "PlayerMoney.h"
#include "ChasingMonster.h"
#include "game_map.h"
#include "ImpTimer.h"
#include "Menu.h"

enum GameState {
    MENU,
    PLAY,
    EXIT
};

class Game {
public:
    Game();
    ~Game();
    void initThreatsList();
    GameState showMenu();
    GameState run();
    bool init();
    void cleanup();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Menu* menu;
    TTF_Font* font_time;

    GameMap* game_map;
    MainObject* p_player;
    BaseObject g_background;


    bool loadBackground();
    void close();
    std::vector<ThreatObject*> MakeThreatList();
    std::vector<ThreatObject*> threats_list;
};

#endif // GAME_H