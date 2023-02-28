#include <PubSubClient.h>
#include <WiFi.h>

#include <Networking.h>
#include <PublicData.h>

PubSubClient mqttclient(client);

namespace MQTT
{
    void initMQTT()
    {
        mqttclient.setServer(SERVER_URL.c_str(), 1883);
        mqttclient.setCallback(callback);
    }

    void callback(char *topic, byte *message, unsigned int length)
    {
    }

    void check_status()
    {
        if (!mqttclient.connected())
        {
            reconnect();
        }
        mqttclient.loop();
    }

    void reconnect()
    {
        while (!mqttclient.connected())
        {
            if (mqttclient.connect("Lamp1"))
            {
                mqttclient.subscribe("lovelamp1/commands");
            }
            else
            {
                delay(5000);
            }
        }
    }

} // namespace MQTT
