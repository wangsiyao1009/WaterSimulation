#ifndef WATERSIMULATION_ROCK_H
#define WATERSIMULATION_ROCK_H

#include <SDL.h>
#include <SDL_render.h>
#include <map>
#include "ColorRGB.h"
#include "Config.h"

using namespace std;

/**
 * 石头
 */
class Rock {

public:
    Rock();

    virtual ~Rock();

    pair<int, int> getPosition();

    void initPositionVisibleAndInWaterFlag(int posX, int posY);

    bool isInWater() const;

    bool isVisible() const;

    void render(SDL_Renderer *renderer);

    void setInWater();

    void update(double timeDuration);

private:
    /**
     * 颜色RGB
     */
    ColorRGB colorRgb;
    /**
     * inWater==true表示岩石已经在水中，不再检测碰撞
     */
    bool inWater;
    /**
     * 矩形的大小和位置
     */
    SDL_Rect rect;
    /**
     * 速度
     */
    double velocity;
    /**
     * visible==false代表岩石已销毁，不再进行渲染和更新
     */
    bool visible;
};

#endif // WATERSIMULATION_ROCK_H
