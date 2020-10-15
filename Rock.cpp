#include "Rock.h"

Rock::Rock() : inWater(false), rect(), velocity(0),
               visible(false), colorRgb(160, 160, 160) {
    rect.w = Config::rockWidth;
    rect.h = Config::rockHeight;
}

Rock::~Rock() = default;

/**
 * 外部获取石头的坐标，查看是否与水发生了碰撞
 */
pair<int, int> Rock::getPosition() {
    return {rect.x, rect.y};
}

/**
 * 初始化坐标，并将inWater设为false、visible标志设为true，使得石头重新可见
 */
void Rock::initPositionVisibleAndInWaterFlag(int posX, int posY) {
    rect.x = posX;
    rect.y = posY;
    inWater = false;
    visible = true;
    velocity = 0;
}

/**
 * 如果石头已在水中，则外部不再检测碰撞
 */
bool Rock::isInWater() const {
    return inWater;
}

/**
 * 默认不能同时生成2个石头，如果石头仍然可见，则鼠标点击无效
 */
bool Rock::isVisible() const {
    return visible;
}

/**
 * 如果刚刚发生了碰撞，则设置该标记，使得之后不再检测碰撞
 */
void Rock::setInWater() {
    this->inWater = true;
}

/**
 * 如果未在水中，则a=gravity，v=v0+a*t，s=v0*t+1/2*a*t*t
 * 如果已在水中，则a=gravity-k/w*v0，v=v0+at，s=v0*t+1/2*a*t*t
 * 其中k/w当前设置为0.25。如果当前的y大于窗口的高度则设置visible为false
 */
void Rock::update(double timeDuration) {
    if (visible) {
        if (!inWater) {
            double accelerate = Config::gravity;
            double lastVelocity = velocity;
            velocity = lastVelocity + accelerate * timeDuration;
            int distance = static_cast<int>(lastVelocity * timeDuration +
                                            1.0 / 2 * accelerate * timeDuration * timeDuration);
            rect.y += distance;
        } else {
            double lastVelocity = velocity;
            double accelerate = Config::gravity - 0.25 * lastVelocity;
            velocity = lastVelocity + accelerate * timeDuration;
            int distance = static_cast<int>(lastVelocity * timeDuration +
                                            1.0 / 2 * accelerate * timeDuration * timeDuration);
            rect.y += distance;
        }
        if (rect.y > Config::windowHeight) {
            visible = false;
        }
    }
}

void Rock::render(SDL_Renderer *renderer) {
    if (visible) {
        SDL_SetRenderDrawColor(renderer, colorRgb.r, colorRgb.g, colorRgb.b, 0);
        SDL_RenderFillRect(renderer, &rect);
    }
}