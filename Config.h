#ifndef WATERSIMULATION_CONFIG_H
#define WATERSIMULATION_CONFIG_H

class Config {

public:
    /**
     * 每次石头溅起的水花数量
     */
    static constexpr unsigned short particleNum = 20;
    /**
     * 窗口高度
     */
    static constexpr unsigned short windowHeight = 600;
    /**
     * 窗口宽度
     */
    static constexpr unsigned short windowWidth = 1024;
    /**
    * 重力加速度
    */
    static constexpr double gravity = 9.8;
    /**
     * 水平面位置
     */
    static constexpr int waterHorizon = 500;
    /**
     * 水柱宽度，将水拆成小的水柱，使得可以模拟水波
     */
    static constexpr int waterColumnWidth = 10;
    /**
    * 石头宽度
    */
    static constexpr int rockWidth = 50;
    /**
     * 石头高度
     */
    static constexpr int rockHeight = 50;
    /**
     * 单个水花宽度
     */
    static constexpr int waterParticleWidth = 10;
    /**
     * 单个水花高度
     */
    static constexpr int waterParticleHeight = 10;

    virtual ~Config();

private:
    Config();

};

#endif // WATERSIMULATION_CONFIG_H
