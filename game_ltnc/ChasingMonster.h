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

    void Move(const MainObject& main_object, const GameMap& game_map);
    void SetSpeed(int speed);
    void Show(SDL_Renderer* des);

private:
    int speed_;
};

#endif // CHASING_MONSTER_H_
