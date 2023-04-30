#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatObject.h" 
#include "ChasingMonster.h"
BaseObject g_background;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Doraemon's Adventure",
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SCREEN_WIDTH, SCREEN_HEIGHT, 
                                SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
    }
    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img/images.jpg", g_screen);
    if (ret == false)
    {
        return false;
    }
    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::vector<ThreatObject*> MakeThreatList()
{
    std::vector<ThreatObject*> list_threats;
    ThreatObject* dynamic_threats = new ThreatObject[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatObject* p_threat = (dynamic_threats + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img/threat_left.png", g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(500 + i * 500);
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos() - 100; 
            int pos2 = p_threat->get_x_pos() + 100;
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);

            list_threats.push_back(p_threat);
        }
    }

    ThreatObject* threat_objs = new ThreatObject[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatObject* p_threat = threat_objs + i;
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img/threat_level.png", g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(700 + i * 1000);
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatObject::STATIC_THREAT);
            p_threat->set_input_left(0);

            //add shoot
            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);

            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}

int main(int argc, char* argv[])
{
    ImpTimer fps_timer;
    ImpTimer chasing_monster_timer;


    if (InitData() == false) {
        return -1;
    }
    if (LoadBackground() == false)
    {
        return -1;
    }

    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImg("img/player_right.png", g_screen);
    p_player.set_clips();

    std::vector<ThreatObject*> threats_list = MakeThreatList();

    //heart
    int num_die = 0;

    bool is_quit = false;

    //Chasing Monster
    ChasingMonster chasing_monster;
    chasing_monster.LoadImg("img/chasing_monster.jpg", g_screen);
    chasing_monster.SetRect(200, 200);
    chasing_monster.SetSpeed(1); // Adjust speed as desired

    while (!is_quit)
    {
        fps_timer.start();
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            p_player.HandleInputAction(g_event, g_screen);
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);
        game_map.DrawMap(g_screen);

        //Call DrawMap to render Tiles
        Map map_data = game_map.getMap();

        p_player.HandleBullet(g_screen);
        p_player.setMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        game_map.setMap(map_data);
        game_map.DrawMap(g_screen);

        //Chasing Monster
        chasing_monster.Move(p_player, game_map);
        chasing_monster.Show(g_screen);

        // Collision check between the chasing monster and the main character
        SDL_Rect rect_player = p_player.GetRect();
        SDL_Rect rect_chasing_monster = chasing_monster.GetRect();
        bool is_collision = SDLCommonFunc::CheckCollision(rect_player, rect_chasing_monster);

        if (is_collision) {
            // Take appropriate action upon collision
            // e.g. reduce player health, restart the level, etc.
            num_die++;
            if (num_die <= 3) {
                p_player.SetRect(0, 0);
                p_player.set_comeback_time(60);
                SDL_Delay(2000);
                continue;
            }
        }
            // You can add more actions here based on your game design

        for (int i = 0; i < threats_list.size(); i++)
        {
            ThreatObject* p_threat = threats_list.at(i);
            if (p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat->ImpMoveType(g_screen);
                p_threat->DoPlayer(map_data);
                p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(g_screen);

                SDL_Rect rect_player = p_player.GetRectFrame();
                bool bCol1 = false;
                std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                for (int ij = 0; ij < tBullet_list.size(); ij++)
                {
                    BulletObject* pt_bullet = tBullet_list.at(ij);
                    if (pt_bullet)
                    {
                        bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
                        if (bCol1)
                        {
                            p_threat->RemoveBullet(ij);
                            break;
                        }
                    }
                }
                SDL_Rect rect_threat = p_threat->GetRectFrame();
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
                if (bCol1 || bCol2)
                {
                    num_die++;
                    if (num_die <= 3)
                    {
                        p_player.SetRect(0, 0);
                        p_player.set_comeback_time(60);
                        SDL_Delay(2000);
                        continue;
                    }
                    /*else
                    {
                        if (MessageBox(NULL, L"Game Over", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
                        {
                            p_threat->Free();
                            close();
                            SDL_Quit();
                            return 0;
                        }
                    }
                    */
                }              
            }
        }
        SDL_RenderPresent(g_screen);

        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list_();
        for (int r = 0; r < bullet_arr.size(); ++r)
        {
            BulletObject* p_bullet = bullet_arr.at(r);
            if (p_bullet)
            {
                for (int t = 0; t < threats_list.size(); ++t)
                {
                    ThreatObject* obj_threat = threats_list.at(t);
                    if (obj_threat)
                    {
                        SDL_Rect tRect;
                        tRect.x = obj_threat->GetRect().x;
                        tRect.y = obj_threat->GetRect().y;

                        tRect.w = obj_threat->get_width_frame();
                        tRect.h = obj_threat->get_height_frame();

                        SDL_Rect bRect = p_bullet->GetRect();

                        bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

                        if (bCol)
                        {
                            p_player.RemoveBullet(r);
                            obj_threat->Free();
                            threats_list.erase(threats_list.begin() + t);
                        }

                    }
                }
            }
        }
        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND;

        if (real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if (delay_time >= 0)
            {
                SDL_Delay(delay_time);
            }
        }
    }

    for (int i = 0; i < threats_list.size(); i++)
    {
        ThreatObject* p_threat = threats_list.at(i);
        if (p_threat)
        {
            p_threat->Free();
            p_threat = NULL;
        }
    }
    threats_list.clear();
    close();
    return 0;
}
