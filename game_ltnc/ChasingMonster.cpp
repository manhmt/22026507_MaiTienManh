#include "ChasingMonster.h"
#include "MainObject.h"
#include "game_map.h"

ChasingMonster::ChasingMonster() : speed_(1), last_move_time_(0), width_frame_(0)
, height_frame_(0) {}
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
			// Keep the monster within the game map boundaries
			if (rect_.x < 0) {
				rect_.x = 0;
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
			if (rect_.y < 0) {
				rect_.y = 0;
			}
			
        }
    }
}


void ChasingMonster::Show(SDL_Renderer* des) {
    Render(des);
}

bool ChasingMonster::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		width_frame_ = rect_.w / 6;
		height_frame_ = rect_.h;
	}
	return ret;
}
SDL_Rect ChasingMonster::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;

	rect.w = width_frame_;
	rect.h = height_frame_;
	return rect;
}
void ChasingMonster::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{


		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = 2 * width_frame_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = 3 * width_frame_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

		frame_clip_[4].x = 4 * width_frame_;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;

		frame_clip_[5].x = 5 * width_frame_;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = height_frame_;

	}
}