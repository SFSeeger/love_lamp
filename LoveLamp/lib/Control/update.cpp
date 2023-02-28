#include <Arduino.h>
#include <HTTPUpdate.h>

#include <Update.h>
#include <Control.h>
#include <PublicData.h>

#define AUTH_HEADER "CHANGE-ME-IMPORTANT"

namespace Updater
{
    void update()
    {
        t_httpUpdate_return ret = httpUpdate.update(client, SERVER_URL, 443, "/firmware/update/", FIRMWARE_VERSION);
        switch (ret)
        {
        case HTTP_UPDATE_FAILED:
            Serial.println("[update] Update failed");
            break;
        case HTTP_UPDATE_NO_UPDATES:
            Serial.println("[update] No Update available");
            break;
        case HTTP_UPDATE_OK:
            Serial.println("[update] Update successful");
            break;
        default:
            break;
        }
    }
}