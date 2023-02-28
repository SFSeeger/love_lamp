#include <Storage.h>

#include <Wifi.h>
#include <WebServer.h>
#include <Dns.h>

IPAddress init_networking(const char *ssid, const char *password)
{
    WiFi.softAP(ssid, password); // init wifi
    return WiFi.softAPIP();
}

IPAddress connectWithWiFi(const char *ssid, Storage::t_Crendentials creds)
{
    WiFi.begin(ssid, creds.password);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println(".");
        delay(1000);
    }
    return WiFi.localIP();
}

namespace WebServer
{
    WebServer server(80);
    static const char root[] PROGMEM = 
    "<html>
        <form action='/submit' method='POST'>
            <label for='password'>Password:</label><br><input type='text' id='password' name='password'>
            <input type='submit'>
        </form>
    </html>";

    namespace Routes
    {
        void handleRoot()
        {
            server.send(200, "text/html", FPSTR(root));
        }

        void sendCredentials()
        {
            String password = server.arg("password");
            // Save Credentials
            Storage::storeCredentials({username, password});
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
}