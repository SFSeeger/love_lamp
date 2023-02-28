#include <Arduino.h>
#include <Renderer.h>
#include <Storage.h>
#include <Networking.h>

void setup()
{
    Storage::initStorage(256);
    WiFiHandler::init_networking("Lamp", "1234");
    WiFiHandler::WebServer::init_server();
}

void loop()
{
    Rendering::render();
}