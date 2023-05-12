#include "Game.h"
Game::Game() :
    window(nullptr),
    renderer(nullptr),
    menu(nullptr),
    game_map(nullptr),
    p_player(nullptr),
    font_time(nullptr) 
{
    // Rest of the constructor code
}

Game::~Game()
{
    cleanup();
}

void Game::initThreatsList() {
    threats_list = MakeThreatList();
}
bool Game::init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    // Create window
    window = SDL_CreateWindow("Adventure",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    //screen = renderer;
    SDL_SetRenderDrawColor(renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    // Load the font
    font_time = TTF_OpenFont("font//dlxfont_.ttf", 35);
    if (font_time == NULL)
    {
        return false;
    }

    // Create the menu
    menu = new Menu(renderer);
    menu->addOption("Play");
    menu->addOption("Options");
    menu->addOption("Exit");

    // Create the game map
    game_map = new GameMap();
    game_map->LoadMap("map/map01.dat");
    game_map->LoadTiles(renderer);

    // Create the player
    p_player = new MainObject();
    p_player->LoadImg("img/player_right.png", renderer);
    p_player->set_clips();
    //p_player.SetRect(150, 50);

    return true;
}
GameState Game::run()
{
    BaseObject g_background;
    ImpTimer fps_timer;
    ImpTimer chasing_monster_timer;
    loadBackground();


    game_map->LoadMap("map/map01.dat");
    game_map->LoadTiles(renderer);


    p_player->LoadImg("img/player_right.png", renderer);
    p_player->set_clips();

    PlayerPower player_power;
    player_power.Init(renderer);


    PlayerMoney player_money;
    player_money.Init(renderer);
    player_money.SetPos(SCREEN_WIDTH * 0.5 - 250, 8);

    threats_list = MakeThreatList();
    int num_die = 0;

    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);

    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);
    UINT mark_value = 0;

    TextObject money_game;
    money_game.SetColor(TextObject::BLACK_TEXT);

    ChasingMonster chasing_monster;
    chasing_monster.LoadImg("img/chasing_monster.jpg", renderer);
    chasing_monster.GetRectFrame();
    chasing_monster.set_clips();
    chasing_monster.SetRect(180, 0);
    chasing_monster.Show(renderer);
    chasing_monster.SetSpeed(1);

    ExplosionObject exp_threat;
    bool tRet = exp_threat.LoadImg("img//exp3.png", renderer);
    //if (!tRet) return -1;
    exp_threat.set_clip();

    bool is_quit = false;
    GameState menuState = GameState::PLAY;
    while (!is_quit)
    {
        //std::cout << "Current game state: " << static_cast<int>(menuState) << std::endl;
        if (menuState == GameState::MENU)
        {
            GameState newState = showMenu();
            if (newState != GameState::MENU) {
                menuState = newState;
            }
            std::cout << "Menu state: " << static_cast<int>(menuState) << std::endl;
        }
        if (menuState == GameState::EXIT)
        {
            is_quit = true;
            break;
        }
        if (menuState == GameState::PLAY) 
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            g_background.Render(renderer, NULL);
            game_map->DrawMap(renderer);
            //std::cout << "drawmap";
            while (SDL_PollEvent(&g_event) != 0)
            {
                if (g_event.type == SDL_QUIT) {
                    is_quit = true;
                    break;
                }
                p_player->HandleInputAction(g_event, renderer);
            }


            //Call DrawMap to render Tiles
            Map map_data = game_map->getMap();

            p_player->HandleBullet(renderer);
            p_player->setMapXY(map_data.start_x_, map_data.start_y_);
            p_player->DoPlayer(map_data);
            p_player->Show(renderer);

            game_map->setMap(map_data);
            game_map->DrawMap(renderer);

            player_power.Show(renderer);
            player_money.Show(renderer);
            //Chasing Monster
            chasing_monster.Move(*p_player, *game_map);
            chasing_monster.Show(renderer);

            // Collision check between the chasing monster and the main character
            SDL_Rect rect_player = p_player->GetRect();
            SDL_Rect rect_chasing_monster = chasing_monster.GetRect();
            bool is_collision = SDLCommonFunc::CheckCollision(rect_player, rect_chasing_monster);

            if (is_collision) {
                // Take appropriate action upon collision
                // e.g. reduce player health, restart the level, etc.
                num_die++;
                if (num_die <= 3) {
                    p_player->SetRect(0, 0);
                    p_player->set_comeback_time(60);
                    SDL_Delay(1000);
                    player_power.Decrease();
                    player_power.Render(renderer);
                }
            }


            // You can add more actions here based on your game design

         // Iterate through threats and perform actions
            for (int i = 0; i < threats_list.size(); i++)
            {
                ThreatObject* p_threat = threats_list.at(i);
                if (p_threat != NULL)
                {
                    p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                    p_threat->ImpMoveType(renderer);
                    p_threat->DoPlayer(map_data);
                    p_threat->MakeBullet(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, p_player->GetRect().x, p_player->GetRect().y);
                    p_threat->Show(renderer);


                    SDL_Rect rect_player = p_player->GetRectFrame();
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
                                std::cout << "pt_bullet and rect_player";
                                //p_threat->RemoveBullet(ij);
                                //break;
                            }
                        }
                    }

                    SDL_Rect rect_threat = p_threat->GetRectFrame();
                    bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
                    //if (bCol1 || bCol2)
                    if (bCol2)
                    {
                        std::cout << "collision between rect_player and rect_threat1";
                        num_die++;
                        if (num_die < 3)
                        {
                            p_player->SetRect(0, 0);
                            p_player->set_comeback_time(40);
                            SDL_Delay(500);
                            break;
                        }


                        else
                        {
                            if (MessageBox(NULL, L"Game Over...", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
                            {
                                p_threat->Free();
                                close();
                                SDL_Quit();
                                return GameState::EXIT;

                            }
                        }
                    }

                }
            }
            int frame_exp_width = exp_threat.get_frame_width();
            int frame_exp_height = exp_threat.get_frame_height();

            std::vector<BulletObject*> bullet_arr = p_player->get_bullet_list_();
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
                                //continue adjust
                                mark_value++;
                                for (int ex = 0; ex < NUM_FRAME_EXP; ++ex)
                                {
                                    int x_pos_ = p_bullet->GetRect().x - frame_exp_width * 0.5;
                                    int y_pos_ = p_bullet->GetRect().y - frame_exp_height * 0.5;

                                    exp_threat.set_frame(ex);
                                    exp_threat.SetRect(x_pos_, y_pos_);
                                    exp_threat.Show(renderer);

                                    //std::cout << "Rendering frame" << std::endl;
                                    //SDL_RenderPresent(renderer);
                                }

                                p_player->RemoveBullet(r);
                                obj_threat->Free();
                                threats_list.erase(threats_list.begin() + t);
                            }

                        }
                    }
                }
            }

            //Show time game
            std::string str_time = "Time: ";
            Uint32 time_val = SDL_GetTicks() / 1000;
            Uint32 val_time =  150 - time_val;
            if (val_time <= 0)
            {
                if (MessageBox(NULL, L"Run out of Time", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
                {
                    is_quit = true;
                    //break;

                }
            }
            else
            {
                std::string str_val = std::to_string(val_time);
                str_time += str_val;

                time_game.SetText(str_time);
                time_game.LoadFromRenderText(font_time, renderer);
                time_game.RenderText(renderer, SCREEN_WIDTH - 200, 15);
            }

            std::string val_str_mark = std::to_string(mark_value);
            std::string strMark("Mark: ");
            strMark += val_str_mark;

            mark_game.SetText(strMark);
            mark_game.LoadFromRenderText(font_time, renderer);
            mark_game.RenderText(renderer, SCREEN_WIDTH * 0.5, 15);

            int money_count = p_player->GetMoneyCount();
            std::string money_str = std::to_string(money_count);

            money_game.SetText(money_str);
            money_game.LoadFromRenderText(font_time, renderer);
            money_game.RenderText(renderer, SCREEN_WIDTH * 0.5 - 200, 15);



            int real_imp_time = fps_timer.get_ticks();
            int time_one_frame = 800 / FRAME_PER_SECOND;

            if (real_imp_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_imp_time;
                if (delay_time >= 0)
                {
                    SDL_Delay(delay_time);
                }
            }
            SDL_RenderPresent(renderer);
        }
    }
    return GameState::EXIT;
}

void Game::cleanup() {
    // Cleanup code here

    if (menu != nullptr) {
        delete menu;
        menu = nullptr;
    }

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    if (game_map != nullptr) {
        delete game_map;
        game_map = nullptr;
    }

    if (p_player != nullptr) {
        delete p_player;
        p_player = nullptr;
    }

    if (font_time != nullptr)
    {
        TTF_CloseFont(font_time);
        font_time = nullptr;
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Game::loadBackground()
{
    bool ret = g_background.LoadImg("img/images.jpg", renderer);
    if (ret == false)
    {
        std::cerr << "Failed to load background image" << std::endl;
        return false;
    }
    return true;
}
void Game::close()
{
    g_background.Free();

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    IMG_Quit();
    SDL_Quit();
}

std::vector<ThreatObject*> Game::MakeThreatList()
{
    std::vector<ThreatObject*> list_threats;

    for (int i = 0; i < 20; i++)
    {
        ThreatObject* p_threat = new ThreatObject;
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img/threat_left.png", renderer);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(500 + i * 400);
            p_threat->set_y_pos(200);

            float pos1 = p_threat->get_x_pos() - 80;
            float pos2 = p_threat->get_x_pos() + 80;
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);

            list_threats.push_back(p_threat);
        }
    }

    for (int i = 0; i < 20; i++)
    {
        ThreatObject* p_threat = new ThreatObject;
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img/threat_level.png", renderer);
            p_threat->set_clips();
            p_threat->set_x_pos(700 + i * 1000);
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatObject::STATIC_THREAT);
            p_threat->set_input_left(0);

            //add shoot
            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, renderer);

            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}

GameState Game::showMenu()
{
    bool menu_active = true;
    int selectedOption = 0;
    bool backgroundLoaded = loadBackground();
    if (!backgroundLoaded) {
        std::cout << "background is not loaded";
    }
    bool menuRendered = false;
    while (menu_active)
    {
        //std::cout << "menu_avtive";
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                menu_active = false;
                return GameState::EXIT;
            }
            else if (g_event.type == SDL_KEYDOWN)
            {
                switch (g_event.key.keysym.sym) {
                case SDLK_UP:
                    menu->moveUp();
                    break;
                case SDLK_DOWN:
                    menu->moveDown();
                    break;
                case SDLK_RETURN:
                case SDLK_KP_ENTER:
                    selectedOption = menu->getSelectedOption();
                    switch (selectedOption) {
                    case START_GAME:
                        menu_active = false;
                        std::cout << "Play button clicked" << std::endl;
                        return GameState::PLAY; // Updated: Return PLAY state
                    case INSTRUCTION:
                        // Show instruction screen
                        break;
                    case QUIT:
                        menu_active = false;
                        return GameState::EXIT;
                    }
                    break;
                default:
                    break;
                }
            }
            else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                selectedOption = menu->processMouseClick(x, y, font_time, renderer);
                if (selectedOption >= 0) {
                    switch (selectedOption) {
                    case START_GAME:
                        menu_active = false;
                        std::cout << "Switching to PLAY state" << std::endl;
                        return GameState::PLAY;
                    case INSTRUCTION:
                        // Show instruction screen
                        break;
                    case QUIT:
                        menu_active = false;
                        return GameState::EXIT;
                    }
                }
            }
        }

        if (!menuRendered)
        {
            // Render the background image

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            g_background.Render(renderer, NULL);
            menu->renderMenu();
            SDL_RenderPresent(renderer);
            menuRendered = true;
            std::cout << "renderMenu";
        }
    }

    return GameState::EXIT;
}