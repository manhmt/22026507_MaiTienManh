
#include "menu.h"
Menu::Menu(SDL_Renderer* renderer) :
    selectedOption(0),
    optionText(),
    menuUpdated(true),
    backgroundTexture(nullptr),
    renderer(renderer)
{
    //nderer = g_screen;  // Add this line
    // ...

    // Initialize the font
    font = TTF_OpenFont("font//dlxfont_.ttf", 48); // Replace with your font file path and desired size
    if (font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    // Load background image and create a texture
    SDL_Surface* backgroundImage = IMG_Load("img//menu.jpg");
    if (backgroundImage == nullptr) {
        std::cerr << "Failed to load background image: " << IMG_GetError() << std::endl;
    }
    else {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundImage);
        SDL_FreeSurface(backgroundImage);
    }
}

Menu::~Menu() {
    SDL_DestroyTexture(backgroundTexture);
    TTF_CloseFont(font);
}

void Menu::addOption(const std::string& option) {
    options.push_back(option);
}

void Menu::renderMenu() {
    if (menuUpdated) {
        std::cout << "Rendering menu option "<< std::endl;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

        // The rest of the renderMenu() function stays the same
        for (int i = 0; i < options.size(); ++i) {
            // Set the text color based on whether the option is selected or not
            std::cout << "Rendering menu option " << i << std::endl;
            if (i == selectedOption) {
                optionText.SetColor(TextObject::WHITE_TEXT);
            }
            else {
                optionText.SetColor(TextObject::BLACK_TEXT);
            }

            // Render the text on the screen at the appropriate position
            optionText.SetText(options[i]);
            optionText.LoadFromRenderText(font, renderer);
            optionText.RenderText(renderer, 250, 160 + i * 60); // Adjust x and y positions as needed
        }

        SDL_RenderPresent(renderer);

        menuUpdated = false;
    }
}

// The rest of the functions stay the same


void Menu::moveUp() {
    if (selectedOption > 0) {
        selectedOption--;
    }
}

void Menu::moveDown() {
    if (selectedOption < options.size() - 1) {
        selectedOption++;
    }
}

int Menu::processMouseClick(int x, int y, TTF_Font* font, SDL_Renderer* renderer)
{
    int textPosX = 250; // The fixed x position of the text
    int verticalSpacing = 600; // The vertical spacing between menu options

    for (int i = 0; i < options.size(); ++i)
    {
        int textWidth, textHeight;
        TTF_SizeText(font, options[i].c_str(), &textWidth, &textHeight);

        int textPosY = 160 + i * verticalSpacing; // Calculate the y position based on the index

        if (x >= textPosX && x <= textPosX + textWidth &&
            y >= textPosY && y <= textPosY + textHeight)
        {
            selectedOption = i;
            return i;
        }
    }

    return -1;
}

