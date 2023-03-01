#ifndef RENDERER_H
#define RENDERER_H
#include <Adafruit_NeoPixel.h>

const unsigned int NUM_PIXEL = 40;
struct t_Pixelinfo
{
    uint16_t pixel;
    uint32_t color;
};

struct t_PixelData
{
    t_Pixelinfo pixelinfo[NUM_PIXEL];
    uint8_t brightness;
};

namespace Rendering
{
    t_PixelData json_to_pixeldata(DynamicJsonDocument doc);

    void update(t_PixelData data);
    void render_from_data(t_PixelData data);
    void render_solid(t_PixelData data);
    void render_symmetrical(t_PixelData data);
    void crossfade(const uint32_t startColor, const uint32_t endColor, unsigned long speed);
    void render();
}

#endif