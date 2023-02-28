#ifndef NETWORKING_H
#define NETWORKING_H

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

} // namespace MQTT

#endif