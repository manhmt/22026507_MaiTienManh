#include "ChasingMonster.h"
#include "MainObject.h"
#include "game_map.h"

ChasingMonster::ChasingMonster() : speed_(1), last_move_time_(0) {}
ChasingMonster::~ChasingMonster() {}

void ChasingMonster::SetSpeed(int speed) {
    speed_ = speed;
}

void ChasingMonster::Move(MainObject& player, const GameMap& game_map) {
    const int MONSTER_CHASING_DELAY = 3000; // Delay in milliseconds
    Uint32 current_time = SDL_GetTicks();

    if (current_time > MONSTER_CHASING_DELAY) {
        int chasing_monster_speed = 1; // Set the speed of the chasing monster

        // Calculate the direction to move towards the player
        int diff_x = player.GetRect().x - rect_.x;
        int diff_y = player.GetRect().y - rect_.y;

        if (abs(diff_x) > abs(diff_y)) {
            // Move horizontally
            if (diff_x > 0) {
                rect_.x += chasing_monster_speed;
            }
            else {
                rect_.x -= chasing_monster_speed;
            }
        }
        else {
            // Move vertically
            if (diff_y > 0) {
                rect_.y += chasing_monster_speed;
            }
            else {
                rect_.y -= chasing_monster_speed;
            }
        }
    }
}


void ChasingMonster::Show(SDL_Renderer* des) {
    Render(des);
}

