#include "Enemy.h"
#include "Hero.h"
#ifndef ENEMY_FAST_H_
#define ENMY_FAST_H_

class EnemyFast : public Enemy {
    public:
        virtual void Move(Hero player, int width, int height);
};

#endif // ENEMY_FAST_H_
