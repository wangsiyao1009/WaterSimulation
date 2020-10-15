#ifndef WATERSIMULATION_WATERPARTICLE_H
#define WATERSIMULATION_WATERPARTICLE_H

#include <SDL_render.h>
#include <cmath>
#include "ColorRGB.h"
#include "Config.h"

/**
 * 水花
 */
class WaterParticle {

public:
    WaterParticle();

    virtual ~WaterParticle();

    void initPositionVisibleSpeed(int posX, int posY, int v, int angle);

    void render(SDL_Renderer *renderer);

    void update(double timeDuration);

private:
    /**
     * 颜色
     */
    ColorRGB colorRgb;
    /**
     * 矩形和坐标
     */
    SDL_Rect rect;
    /**
     * 是否可见，不可见类似于销毁
     */
    bool visible;
    /**
     * X方向速度
     */
    double velocityX;
    /**
     * Y方向速度
     */
    double velocityY;

};

#endif // WATERSIMULATION_WATERPARTICLE_H
