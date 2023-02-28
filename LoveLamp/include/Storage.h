#ifndef STORAGE_H
#define STORAGE_H
#include <Arduino.h>

struct t_Credentials
{
    String SSID;
    String passwd;
};
namespace Storage
{
    void storeCredentials(t_Credentials creds);

    t_Credentials readCredentials();
    void deleteCredentials();
    bool has_credentials();
    void initStorage(size_t size);
}

#endif