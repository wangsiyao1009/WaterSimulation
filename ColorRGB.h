#ifndef WATERSIMULATION_COLORRGB_H
#define WATERSIMULATION_COLORRGB_H

/**
 * RGB结构体
 */
class ColorRGB {
public:
    ColorRGB(unsigned char r, unsigned char g, unsigned char b);

    virtual ~ColorRGB();

    unsigned char b;
    unsigned char g;
    unsigned char r;
};

#endif // WATERSIMULATION_COLORRGB_H