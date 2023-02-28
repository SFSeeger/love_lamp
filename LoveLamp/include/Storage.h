#include <EEPROM.h>
#include <Arduino.h>

namespace Storage
{
    struct t_Credentials
    {
        String SSID;
        String passwd;
    };

    void storeCredentials(t_Credentials creds)
    {
        EEPROM.write(0, 0x55);
        EEPROM.put(1, creds);
        EEPROM.commit();
    }

    t_Credentials readCredentials()
    {
        struct t_Credentials creds;
        EEPROM.get(1, creds);
        return creds;
    }

    void deleteCredentials()
    {
        EEPROM.write(0, 0x00);
    }

    bool has_credentials()
    {
        return EEPROM.read(0) == 0x55;
    }

    void initStorage(size_t size)
    {
        EEPROM.begin(size);
    }
}