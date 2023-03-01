#include <Adafruit_NeoPixel.h>
#include <Renderer.h>
#include <ArduinoJson.h>

#define NUM_PIXEL_SIDE 10
#define NUM_PIXEL_COL 2
#define PIN 6

Adafruit_NeoPixel leds(NUM_PIXEL, PIN, NEO_RGBW + NEO_KHZ800);

namespace Rendering
{
    t_PixelData json_to_pixeldata(DynamicJsonDocument doc)
    {
        t_PixelData pdata;
        pdata.brightness = doc["brightness"];
        JsonArray values = doc["values"].as<JsonArray>();

        unsigned int i = 0;
        for (JsonObject data : values)
        {
            t_Pixelinfo pinfo;
            pinfo.pixel = data["pixel"].as<int>();
            pinfo.color = data["color"].as<u_int32_t>();
            pdata.pixelinfo[i++] = pinfo;
        }
        return pdata;
    }

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

    void render_symmetrical(t_PixelData data)
    {
        for (t_Pixelinfo info : data.pixelinfo)
        {
            leds.setPixelColor(info.pixel, info.color);
            leds.setPixelColor(info.pixel + NUM_PIXEL_SIDE, info.color);
            leds.setPixelColor(info.pixel + 2 * NUM_PIXEL_SIDE, info.color);
            leds.setPixelColor(info.pixel + 3 * NUM_PIXEL_SIDE, info.color);
        }
        update(data);
    }

    void crossfade(const uint32_t startColor, const uint32_t endColor, unsigned long speed)
    {
    }

    void render()
    {
    }
}
