#include "ChasingMonster.h"
#include "MainObject.h"
#include "game_map.h"

ChasingMonster::ChasingMonster() : speed_(1) {}

ChasingMonster::~ChasingMonster() {}
void ChasingMonster::SetSpeed(int speed) {
    speed_ = speed;
}
/*void ChasingMonster::Move(const MainObject& main_object, const GameMap& game_map) {
    int chasing_monster_speed = 1; // Set the speed of the chasing monster
    rect_.x += chasing_monster_speed; // Update the x position of the chasing monster

    /* Check for a collision with the map
    bool is_collide_map = CheckMapCollision(g_map);
    if (is_collide_map)
    {
        rect_.x -= chasing_monster_speed; // Undo the movement if there's a collision
    }
    
}*/

void ChasingMonster::Move(MainObject player, GameMap& game_map) {
    // Get the current map data
    Map map_data = game_map.getMap();

    // Get player's position in map coordinates
    int player_map_x = player.GetRect().x;
    int player_map_y = player.GetRect().y;

    // Convert player's position to screen coordinates
    SDL_Point player_screen_coords = game_map.ToScreenCoordinates(player_map_x, player_map_y, map_data);

    // Calculate direction vector (player_position - monster_position)
    int dir_x = player_screen_coords.x - rect_.x;
    int dir_y = player_screen_coords.y - rect_.y;

    // Calculate distance between player and monster
    float distance = sqrt(dir_x * dir_x + dir_y * dir_y);

    // Normalize direction vector
    float norm_x = dir_x / distance;
    float norm_y = dir_y / distance;

    // Adjust the speed based on the distance
    float speed;
    speed = 1;


    // Update monster's position based on speed and direction
    rect_.x += static_cast<int>(norm_x * speed);
    rect_.y += static_cast<int>(norm_y * speed);

    // Check for collisions with the map
    //CheckMapCollision(game_map);
}

void ChasingMonster::Show(SDL_Renderer* des) {
    Render(des);
}
