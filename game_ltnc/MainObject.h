#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"


#define  GRAVITY_SPEED 0.4f;
static constexpr double MAX_FALL_SPEED = 10.0; // Adjust the value as needed
#define  PLAYER_SPEED 8;
#define PLAYER_JUMP_VALUE 14;
class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	enum WalkType
	{
		WALK_NONE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
	};
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();

	void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);
	void setMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; };
	void centerEntityOnMap(Map& map_data);
	void UpdateImagePlayer(SDL_Renderer* des);
	SDL_Rect GetRectFrame();

	void set_bullet_list(std::vector<BulletObject*> bullet_list_)
	{
		p_bullet_list_ = bullet_list_;
	}
	std::vector<BulletObject*> get_bullet_list_() const { return p_bullet_list_; }
	void HandleBullet(SDL_Renderer* des);
	void RemoveBullet(const int& idx);
	void IncreaseMoney();

	void set_comeback_time(const int& cb_time) { come_back_time_ = cb_time; }

	float GetXPos() const { return x_pos_; }
	float GetYPos() const { return y_pos_; }
	
	int GetMoneyCount() const { return money_count; }
private:
	std::vector<BulletObject*> p_bullet_list_;
	int money_count;

	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[8];
	Input input_type_;
	int frame_;
	int status_;
	bool on_ground_;

	int map_x_;
	int map_y_;

	int come_back_time_;
};
#endif