#include <iostream>
#include "Enemy_fast.h"
#include "Hero.h"
#include <math.h>
#define PI 3.14159

void EnemyFast::Move(Hero player, int width, int height) {
    int x_dist = std::abs(rect.x - player.rect.x);
    int y_dist = std::abs(rect.y - player.rect.y);
    float ang;

    x_vel = 0;
    y_vel = 0;
    // Q1 || Q4
    if (rect.x < player.rect.x) {
        /// Q1
        if (rect.y < player.rect.y) {
            // ++ quadrant
        }
        //Q4
        else {
            // +- quadrant
            y_dist *= -1;
        }
    }
    // Q2 || Q3
    else {
        // Q2
        if (rect.y < player.rect.y) {
            x_dist *= -1;
        }
        // Q3
        else {
            x_dist *= -1;
            y_dist *= -1;
        }
    }
    angle = std::round(std::atan2(y_dist, x_dist) * (180 / PI)) + 90;
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
