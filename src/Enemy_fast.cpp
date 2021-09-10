#include <iostream>
#include "Enemy_fast.h"
#include "globals.h"
#include "Hero.h"
#include <math.h>

void EnemyFast::Move(Hero player, int width, int height) {


    x_vel = 0;
    y_vel = 0;
    angle = PointTo(rect, player.rect.x, player.rect.y);
    // Follow player logic
    if (rect.x < player.rect.x) {
        x_vel = 4;
    }
    if (rect.x > player.rect.x) {
        x_vel = -4;
    }
    if (rect.y < player.rect.y) {
        y_vel = 4;
    }
    if (rect.y > player.rect.y) {
        y_vel = -4;
    }

    rect.x += x_vel;
    rect.y += y_vel;

    if (rect.x < 0) {
         rect.x = 0;
    }
    else if (rect.x + rect.w > width) {
        rect.x = width - rect.w;
    }
    if (rect.y < 0) {
        rect.y = 0;
    }
    else if (rect.y + rect.h > height) {
        rect.y = height - rect.h;
    }
}
