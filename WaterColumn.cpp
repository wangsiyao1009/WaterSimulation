#include <SDL_rect.h>
#include <SDL_render.h>
#include "WaterColumn.h"
#include <iostream>
using namespace std;

/**
 * 初始化x位置，和宽度，默认高度和y坐标为水平面
 */
WaterColumn::WaterColumn(int positionX) : rect(), velocity(0),
                                          colorRgb(10, 105, 148) {
    rect.x = positionX;
    rect.w = Config::waterColumnWidth;
    rect.y = Config::waterHorizon;
    rect.h = Config::windowHeight - Config::waterHorizon;
}

WaterColumn::~WaterColumn() = default;

/**
 * 获得当前水柱的高度，用于水波的更新
 */
int WaterColumn::getHeight() const {
    return rect.h;
}

/**
 * 获取X位置，查看是哪一个waterColumn碰撞到了石头
 */
int WaterColumn::getPositionX() const {
    return rect.x;
}

void WaterColumn::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, colorRgb.r, colorRgb.g, colorRgb.b, 0);
    SDL_RenderFillRect(renderer, &rect);
}

/**
 * 出现水波时需要根据临近的水柱高度来更新高度
 */
void WaterColumn::updateHeight(int heightDiff) {
    rect.h += heightDiff;
    rect.y -= heightDiff;
}

/**
 * 当出现水波时需要根据临近的高度差来更新当前水波的速度
 */
void WaterColumn::updateVelocity(int velocityDiff) {
    this->velocity += velocityDiff;
}

/**
 * 由胡克定律，当水柱偏离水平面的高度时，更新速度和高度，
 * 使之慢慢接近水平面。x=height-waterHorizon。a=x/W，velocityY=vy0+a*timeDuration，s=vy0*timeDuration+1/2*a*timeDuration*timeDuration
 */
void WaterColumn::update(double timeDuration) {
    int heightDiff = rect.y - Config::waterHorizon;
	//cout << heightDiff << endl;
    double accelerate = 1.0 * heightDiff;
    double lastVelocity = velocity * 0.85;//摩擦速度衰减
    velocity = lastVelocity + accelerate * timeDuration;
    int distance = static_cast<int>(lastVelocity * timeDuration + 1.0 / 2 * accelerate * timeDuration * timeDuration);
    rect.h += distance;
    rect.y -= distance;
}
