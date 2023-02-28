#include <Storage.h>

#include <Wifi.h>
#include <WebServer.h>
#include <DNSServer.h>

IPAddress init_networking(const char *ssid, const char *password)
{
    WiFi.softAP(ssid, password); // init wifi
    return WiFi.softAPIP();
}

IPAddress connectWithWiFi(t_Credentials creds)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(creds.SSID.c_str(), creds.passwd.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println(".");
        delay(1000);
    }
    return WiFi.localIP();
}

WebServer server(80);
static const char root[] PROGMEM = "<html><form action='/submit' method='POST'><label for='ssid'>SSID:</label><br><input type='text' id='ssid' name='ssid'><label for='password'>Password:</label><br><input type='password' id='password' name='password'><input type='submit'></form></html>";

namespace Routes
{
    void handleRoot()
    {
        server.send(200, "text/html", FPSTR(root));
    }

    void sendCredentials()
    {
        String ssid = server.arg("ssid");
        String password = server.arg("password");
        // Save Credentials
        Storage::storeCredentials({ssid, password});
        // Set Global State
        // GlobalState::State.isRunning = true;
        server.send(200, "text/html", "You can close this page now");
    }
}

void init_server()
{
    server.begin();
    server.on("/", Routes::handleRoot);
    server.on("/submit", Routes::sendCredentials);
}

void run()
{
    server.handleClient();
}
