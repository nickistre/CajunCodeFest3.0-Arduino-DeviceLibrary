// Base class for device communication code

// Uncomment the following to put this device into debug mode
//#define DEVICE_DEBUG

#ifndef DEVICE_H
#define DEVICE_H

#include "Arduino.h";
#include "DeviceMessage.h";

class Device
{
  public:
    /*
     * Constructor to setup Device object
     */
    Device(unsigned int deviceId);
     
  protected:
    unsigned int deviceId;
    unsigned int messageCount = 0;
    
    void buildMessage(String data, String type, DeviceMessage &deviceMessage);
    void messageToString(DeviceMessage message, String &messageString);
    boolean stringToMessage(String messageString, DeviceMessage &message);
    void cloneMessage(DeviceMessage sourceMessage, DeviceMessage &targetMessage);
    
  private:  
    void debug(String message);
    void debug(char charMessage[]);
    void debug(char charMessage1[], char charMessage2[]);
    void debug(char charMessage1[], String message2);
    void debug(char charMessage1[], boolean message2);
    
};

#endif DEVICE_H
