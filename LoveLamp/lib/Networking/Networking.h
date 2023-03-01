#ifndef NETWORKING_H
#define NETWORKING_H
#include <Storage.h>

namespace WiFiHandler
{

    IPAddress init_networking(const char *ssid, const char *password);
    IPAddress connectWithWiFi(t_Credentials creds);
    void setupDNS(const char *hostname);

    namespace Webserver
    {
        namespace Routes
        {
            void handleRoot();
            void sendCredentials();
        }

        void init_server();
        void run();
    }
}

namespace MQTT
{
    void initMQTT();
    void check_status();

    void callback(char *topic, byte *message, unsigned int length);
    void reconnect();

} // namespace MQTT

#endif