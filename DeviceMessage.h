// Device message struct used by other Device libraries

#ifndef DEVICE_MESSAGE_H
#define DEVICE_MESSAGE_H

#include "Arduino.h"

// Define constants used for messages
#define MESSAGE_DELIM '|'
#define MESSAGE_END   '\n'
#define MESSAGE_MAX_SIZE 256

struct DeviceMessage {
  unsigned int deviceId;
  unsigned int messageId;
  unsigned int targetDeviceId;
  String type;
  String data;
};


#endif DEVICE_MESSAGE_H
