#ifndef CHASING_MONSTER_H_
#define CHASING_MONSTER_H_

#include "BaseObject.h"
#include "CommonFunc.h"
#include "MainObject.h"
#include "game_map.h"
class ChasingMonster : public BaseObject {
public:
    ChasingMonster();
    ~ChasingMonster();

    void Move(MainObject& player, const GameMap& game_map);
    void SetSpeed(int speed);
    void Show(SDL_Renderer* des);

private:
    int speed_;
    int last_move_time_;
};

#endif // CHASING_MONSTER_H_
