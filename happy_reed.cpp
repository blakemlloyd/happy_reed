#include "Arduino.h"
#include "happy_reed.h"

happy_reed::happy_reed(int pin, PubSubClient client)
{
    pinMode(pin, INPUT);
    _pin = pin;
    _client = client;
}

void happy_reed::setId(char* id)
{
    reedConfigTopic = (char*)malloc(strlen(id) + 28 + 16 + 1);
    snprintf(reedConfigTopic, strlen(id) + 28 + 16, "homeassistant/binary_sensor/%s-reed-%d/config", id, _pin);
    
    reedConfig = (char*)malloc(strlen(id) + 10 + 7 + 30 + 1);
    snprintf(reedConfig, strlen(id) + 10 + 7 + 30, "{\"name\": \"%s-reed-%d\", \"device_class\":\"opening\"}", id, _pin);
    
    reedTopic = (char*)malloc(strlen(id) + 43 + 1);
    snprintf(reedTopic, strlen(id) + 41, "homeassistant/binary_sensor/%s-reed-%d/state", id, _pin);
    
    _client.publish(reedConfigTopic, reedConfig, true);
}

bool happy_reed::checkState()
{
    int tmpButtonState = digitalRead(_pin);
    if(tmpButtonState != _state)
    {
        _state = tmpButtonState;
        if(_state == LOW) //closed
        {
            _client.publish(reedTopic, "OFF");
        }
        else //open
        {
            _client.publish(reedTopic, "ON");
        }
        return true;
    }
    return false;
}