#include <PubSubClient.h>
#include <ArduinoJson.h>

#include <Networking.h>
#include <PublicData.h>
#include <Renderer.h>

PubSubClient mqttclient(client);

const char *TOPIC_LOCAL = "lovelamp1/commands";
const char *TOPIC_PAIR = "pair1/commands";

namespace MQTT
{
    void initMQTT()
    {
        mqttclient.setServer(SERVER_URL.c_str(), 1883);
        mqttclient.setCallback(callback);
    }

    void callback(char *topic, byte *message, unsigned int length)
    {
        if (topic == TOPIC_LOCAL | topic == TOPIC_PAIR)
        {
            DynamicJsonDocument doc(2048);
            deserializeJson(doc, message);
            t_PixelData data = Rendering::json_to_pixeldata(doc);
            Rendering::render_from_data(data);
        }
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
                mqttclient.subscribe(TOPIC_LOCAL);
                mqttclient.subscribe(TOPIC_PAIR);
            }
            else
            {
                delay(5000);
            }
        }
    }

} // namespace MQTT
