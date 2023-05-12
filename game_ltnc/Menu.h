#ifndef MENU_H
#define MENU_H

#include "CommonFunc.h"
#include <string>
#include <vector>
#include "TextObject.h"

enum MenuOption {
    START_GAME,
    INSTRUCTION,
    QUIT
};
class Menu {
public:
    Menu(SDL_Renderer* renderer);
    ~Menu();
    void addOption(const std::string& option);
    void renderMenu();
    int getSelectedOption() const { return selectedOption; }
    void moveUp();
    void moveDown();
    int processMouseClick(int x, int y, TTF_Font* font, SDL_Renderer* renderer);
private:
    SDL_Renderer* renderer;
    std::vector<std::string> options;
    int selectedOption;
    TextObject optionText;
    TTF_Font* font; 
    bool menuUpdated;
    SDL_Texture* backgroundTexture;


};

#endif