#include <Arduino.h>
#include <Update.h>

namespace Updater
{
    int update(size_t size, Buffer *buf)
    {
        if (!Update.begin(size, ledPin = LED_BUILTIN))
        {
            Update.printError(Serial);
            return -1;
        }
        else if (Update.write(buf, size) != size)
        {
            Update.printError(Serial);
            return -1;
        }
        else if (Update.end(true))
        {
            Serial.printf("Update Success: %u\nRebooting...\n", size);
            return 0;
        }
    }
}