#ifndef WATERSIMULATION_WATERSIMULATION_H
#define WATERSIMULATION_WATERSIMULATION_H

#include "Rock.h"
#include "WaterColumn.h"
#include "WaterParticle.h"
#include <vector>

using namespace std;

/**
 * 水，可以产生水花、波纹
 */
class WaterSimulation {

public:
    WaterSimulation();

    virtual ~WaterSimulation();

    void eventLoop();

private:
    /**
     * SDL事件
     */
    SDL_Event event;
    /**
     * 渲染器
     */
    SDL_Renderer *renderer;
    /**
     * 岩石
     */
    Rock rock;

    /**
     * 水柱
     */
    vector<WaterColumn> waterColumns;
    /**
     * 水花
     */
    vector<WaterParticle> waterParticles;
    /**
     * 窗口
     */
    SDL_Window *window;

    void collision();

    void render();

};

#endif // WATERSIMULATION_WATERSIMULATION_H
