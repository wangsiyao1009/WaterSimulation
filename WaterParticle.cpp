#include "WaterParticle.h"

WaterParticle::WaterParticle() : rect(), visible(false),
                                 velocityX(0), velocityY(0), colorRgb(10, 105, 148) {
    rect.w = Config::waterParticleWidth;
    rect.h = Config::waterParticleHeight;
}

WaterParticle::~WaterParticle() = default;

/**
 * 坐标，速度，角度，并设置可见为true
 */
void WaterParticle::initPositionVisibleSpeed(int posX, int posY, int v, int angle) {
    rect.x = posX;
    rect.y = posY;
    double angleArc = 2 * M_PI * angle / 360;
    velocityX = 1.0 * v * std::cos(angleArc);
    velocityY = -1.0 * v * std::sin(angleArc);
    visible = true;
}

/**
 * a=gravity，velocityY=vy0+a*t, sy=vy0*t+1/2*a*t*t。
 * 如果当前的y大于水平面高度则设置visible为false
 */
void WaterParticle::update(double timeDuration) {
    if (visible) {
        double accelerate = Config::gravity;
        double lastVelocityY = velocityY;
        velocityY = lastVelocityY + accelerate * timeDuration;
        int distanceY = static_cast<int>(lastVelocityY * timeDuration +
                                         1.0 / 2 * accelerate * timeDuration * timeDuration);
        rect.y += distanceY;
        int distanceX = static_cast<int>(velocityX * timeDuration);
        rect.x += distanceX;
        if (rect.y > Config::waterHorizon) {
            visible = false;
        }
    }
}

void WaterParticle::render(SDL_Renderer *renderer) {
    if (visible) {
        SDL_SetRenderDrawColor(renderer, colorRgb.r, colorRgb.g, colorRgb.b, 0);
        SDL_RenderFillRect(renderer, &rect);
    }
}
