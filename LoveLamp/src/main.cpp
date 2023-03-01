#include <Arduino.h>
#include <Renderer.h>
#include <Storage.h>
#include <Networking.h>

void setup()
{
    Storage::initStorage(256);
    if (!Storage::has_credentials())
    {
        WiFiHandler::init_networking("Lamp", "1234");
        WiFiHandler::setupDNS("lovelamp");
        WiFiHandler::Webserver::init_server();
    }
    else
    {
        WiFiHandler::connectWithWiFi(Storage::readCredentials());
        MQTT::initMQTT();
    }
}

void loop()
{
    MQTT::check_status();
}