#ifndef happy_reed_h
#define happy_reed_h

#include "Arduino.h"
#include <PubSubClient.h>

class happy_reed
{
    public:
        happy_reed(int pin, PubSubClient client);
        void setId(char* id);
        bool checkState();
    private:
        int _pin;
        int _state;
        char *reedConfigTopic;
        char *reedConfig;
        char *reedTopic;
        PubSubClient _client;
};

#endif