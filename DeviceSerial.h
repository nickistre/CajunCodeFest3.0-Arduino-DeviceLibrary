// Classes to manage concept of "devices". This will manage
// Serial and RF communications

// Uncomment the following and recompile to put DeviceSerial class into debug mode
#define DEVICE_SERIAL_DEBUG

#ifndef DEVICE_SERIAL_H
#define DEVICE_SERIAL_H

#include "Arduino.h";
#include "DeviceMessage.h";
#include "Device.h";

#define DEVICE_SERIAL_DEFAULT_TIMEOUT 1000

class DeviceSerial: public Device {
  public:
    DeviceSerial(unsigned int deviceId);
    
    /*
     * Setup the serial connection to send and
     * receive messages with a host computer
     */
    void init();
    
    /*
     * Sends a message through the serial connection
     */
    //int send(char* data);
    //int send(String data);
    int send(char* data, char* type);
    int send(String data, char* type);
    int send(String data, String type);
    int sendMessage(DeviceMessage deviceMessage);
    
    /*
     * Whether there is a message available to receive
     */
    boolean available(unsigned int time);
    boolean available();
    
    /*
     * Retrieve the current message, if there is one
     */
    boolean receiveMessage(DeviceMessage &message, unsigned int time);    
    boolean receiveMessage(DeviceMessage &message);
    
  protected:
    boolean hasMessage = false;
    DeviceMessage currentMessage;
    char buffer[MESSAGE_MAX_SIZE];
    
    void lookForMessage(unsigned int time);
    
  private:
    void debug(String message);
    void debug(char charMessage[]);
    void debug(char charMessage1[], char charMessage2[]);
    void debug(char charMessage1[], String message2);
    void debug(char charMessage1[], boolean message2);
    
};

#endif DEVICE_SERIAL_H
