#include <Arduino.h>
#include <Storage.h>

void (*resetFunc)(void) = 0;

namespace Control
{
    void setup();
    void reset();
    void detect_button();
}

namespace Updater
{
    void update();
}