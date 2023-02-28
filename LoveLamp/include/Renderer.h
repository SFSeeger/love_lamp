#include <Adafruit_NeoPixel.h>

#define NUM_PIXEL 40
#define NUM_PIXEL_SIDE 10
#define NUM_PIXEL_COL 2
#define PIN 6

namespace Rendering
{

    Adafruit_NeoPixel leds(NUM_PIXEL, PIN, NEO_RGBW + NEO_KHZ800);

    void (*state_func)(Adafruit_NeoPixel *pixels) = nullptr;

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

    void update(t_PixelData data)
    {
        leds.setBrightness(data.brightness);
        leds.show();
    }

    void render_from_data(t_PixelData data)
    {
        for (t_Pixelinfo info : data.pixelinfo)
        {
            leds.setPixelColor(info.pixel, info.color);
        }
        update(data);
    }

    void render_solid(t_PixelData data)
    {
        for (int i = 0; i < NUM_PIXEL; i++)
        {
            leds.setPixelColor(i, data.pixelinfo[0].color);
        }
        update(data);
    }

    void render_symmetrical(t_PixelData data){
        for (t_Pixelinfo info : data.pixelinfo)
        {
            leds.setPixelColor(info.pixel, info.color);
            leds.setPixelColor(info.pixel+NUM_PIXEL_SIDE, info.color);
            leds.setPixelColor(info.pixel+2*NUM_PIXEL_SIDE, info.color);
            leds.setPixelColor(info.pixel+3*NUM_PIXEL_SIDE, info.color);
        }
        update(data);
    }

    void crossfade(const uint32_t startColor, const uint32_t endColor, unsigned long speed)
    {
    }

    void render()
    {
        state_func(&leds);
    }
}