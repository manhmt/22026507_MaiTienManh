#include "CommonFunc.h"
/*SDL_Surface* SDLCommonFunc::LoadImg(const std::string& file_path)
{
    SDL_Surface* loaded_image = IMG_Load(file_path.c_str());
    if (loaded_image == NULL)
    {
        std::cout << "Error loading image: " << IMG_GetError() << std::endl;
    }
    return loaded_image;
}

SDL_Rect SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* dest, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(src, NULL, dest, &offset);
    return offset;  
}
bool SDLCommonFunc::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
    if (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}
/*int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font)
{
    g_img_menu = LoadImg("img//start_img.png");
    if (g_img_menu == NULL)
        return 0;
    const int kMenuItemNum = 2;
    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 200;
    pos_arr[0].y = 400;

    pos_arr[1].x = 200;
    pos_arr[1].y = 200;

    TextObject text_menu[kMenuItemNum];

    text_menu[0].SetText("Play Game");
    text_menu[0].SetColor(TextObject::BLACK_TEXT);
    text_menu[0].LoadFromRenderText(font, g_screen);
    text_menu[0].RenderText(g_screen, SCREEN_WIDTH - 200, 15);

    text_menu[1].SetText("Exit Game");
    text_menu[1].SetColor(TextObject::BLACK_TEXT);
    text_menu[1].LoadFromRenderText(font, g_screen);
    text_menu[1].RenderText(g_screen, SCREEN_WIDTH - 200, 15 + text_menu[0].GetHeight());
    
    bool selected[kMenuItemNum] = { 0, 0 };

    int xm = 0;
    int ym = 0;

    SDL_Event m_event;
    while (true)
    {
        SDLCommonFunc::ApplySurface(g_img_menu, des, 0, 0);
        for (int i = 0; i < kMenuItemNum; i++)
        {
            text_menu[1].CreateGameText(font, des);
        }
        while (SDL_PollEvent(&m_event)
        { 
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event
            }
            default:
                break;
            }
        }
    }
    
}


int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font)
{
    g_img_menu = LoadImg("img//start_img.jpg");
    if (g_img_menu == NULL)
        return 0;
    const int kMenuItemNum = 2;
    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 200;
    pos_arr[0].y = 200;

    pos_arr[1].x = 200;
    pos_arr[1].y = 400;

    TextObject text_menu[kMenuItemNum];

    text_menu[0].SetText("Play Game");
    text_menu[0].SetColor(TextObject::BLACK_TEXT);
    text_menu[0].LoadFromRenderText(font, g_screen);

    text_menu[1].SetText("Exit Game");
    text_menu[1].SetColor(TextObject::BLACK_TEXT);
    text_menu[1].LoadFromRenderText(font, g_screen);

    bool selected[kMenuItemNum] = { 0, 0 };

    int xm = 0;
    int ym = 0;

    SDL_Event m_event;
    while (true)
    {
        SDLCommonFunc::ApplySurface(g_img_menu, des, 0, 0);
        for (int i = 0; i < kMenuItemNum; i++)
        {
            text_menu[i].RenderText(g_screen, pos_arr[i].x, pos_arr[i].y);
        }
        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;
                for (int i = 0; i < kMenuItemNum; i++)
                {
                    if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            text_menu[i].SetColor(TextObject::RED_TEXT);
                            text_menu[i].LoadFromRenderText(font, g_screen);
                        }
                    }
                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            text_menu[i].SetColor(TextObject::BLACK_TEXT);
                            text_menu[i].LoadFromRenderText(font, g_screen);
                        }
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.button.x;
                ym = m_event.button.y;
                for (int i = 0; i < kMenuItemNum; i++)
                {
                    if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
                    {
                        return i; // return the selected menu item index
                    }
                }
            }
            break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 1;
                }
            default:
                break;
            }
        }

        //SDL_Delay(100); // Add a small delay to avoid high CPU usage
    }

        SDL_Flip(des); // Update the screen
    return 1; // Return -1 if the menu loop is somehow exited without a
}


SDL_Texture* SDLCommonFunc::LoadTexture(SDL_Renderer* renderer, const std::string& file_path)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, file_path.c_str());
    if (texture == NULL)
    {
        std::cout << "Error loading texture: " << IMG_GetError() << std::endl;
    }
    return texture;
}

SDL_FRect SDLCommonFunc::ApplyTexture(SDL_Texture* texture, SDL_Renderer* renderer, float x, float y, float w, float h)
{
    SDL_FRect rect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    return rect;
}

bool SDLCommonFunc::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
    if (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}

int SDLCommonFunc::ShowMenu(SDL_Renderer* renderer, TTF_Font* font)
{
    SDL_Texture* texture = LoadTexture(renderer, "img/start_img.jpg");
    if (texture == NULL)
    {
        return 0;
    }

    const int kMenuItemNum = 2;
    SDL_FRect pos_arr[kMenuItemNum];
    pos_arr[0].x = 200;
    pos_arr[0].y = 200;
    pos_arr[0].w = 0;
    pos_arr[0].h = 0;

    pos_arr[1].x = 200;
    pos_arr[1].y = 400;
    pos_arr[1].w = 0;
    pos_arr[1].h = 0;

    TextObject text_menu[kMenuItemNum];

    text_menu[0].SetText("Play Game");
    text_menu[0].SetColor(TextObject::BLACK_TEXT);
    text_menu[0].LoadFromRenderText(font, renderer);

    text_menu[1].SetText("Exit Game");
    text_menu[1].SetColor(TextObject::BLACK_TEXT);
    text_menu[1].LoadFromRenderText(font, renderer);

    bool selected[kMenuItemNum] = { false, false };

    int xm = 0;
    int ym = 0;

    SDL_Event m_event;
    while (true)
    {
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        for (int i = 0; i < kMenuItemNum; i++)
        {
            text_menu[i].RenderText(renderer, pos_arr[i].x, pos_arr[i].y);
        }

        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;
                for (int i = 0; i < kMenuItemNum; i++)
                {
                    if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            text_menu[i].SetColor(TextObject::RED_TEXT);
                            text_menu[i].LoadFromRenderText(font, g_screen);
                        }
                    }
                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            text_menu[i].SetColor(TextObject::BLACK_TEXT);
                            text_menu[i].LoadFromRenderText(font, g_screen);
                        }
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.button.x;
                ym = m_event.button.y;
                for (int i = 0; i < kMenuItemNum; i++)
                {
                    if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
                    {
                        return i;
                    }
                }
            }
            break;
            default:
                break;
            }
        }

    }
*/
bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

/*bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    if (object1.x + object1.w <= object2.x ||
        object2.x + object2.w <= object1.x ||
        object1.y + object1.h <= object2.y ||
        object2.y + object2.h <= object1.y)
    {
        return false;
    }
    return true;
}*/
