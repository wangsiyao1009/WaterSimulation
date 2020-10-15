#ifndef WATERSIMULATION_WATERCOLUMN_H
#define WATERSIMULATION_WATERCOLUMN_H

#include <SDL_rect.h>
#include <SDL_render.h>
#include "ColorRGB.h"
#include "Config.h"

/**
 * 水的基本单位，水柱可以上下移动，模拟水波的效果
 */
class WaterColumn {

public:

    explicit WaterColumn(int positionX);

    virtual ~WaterColumn();

    int getHeight() const;

    void render(SDL_Renderer *renderer);

    void update(double timeDuration);

    void updateHeight(int heightDiff);

    void updateVelocity(int velocityDiff);

private:
    /**
     * 颜色
     */
    ColorRGB colorRgb;
    /**
     * 矩形大小和位置
     */
    SDL_Rect rect;
    /**
     * Y方向速度
     */
    double velocity;

};

#endif // WATERSIMULATION_WATERCOLUMN_H
