#include "Arduino.h";
#include "DeviceSerial.h";


// Class Constructor
DeviceSerial::DeviceSerial(unsigned int deviceId)
  : Device(deviceId)
{
  
}

// Serial port functions

void DeviceSerial::init()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait until Serial is initialized on some arduino boards
  }
}

int DeviceSerial::send(char* data, char* type)
{
  return this->send(String(data), String(type));
}

int DeviceSerial::send(String data, char* type)
{
  return this->send(data, String(type));
}

int DeviceSerial::send(String data, String type)
{
  DeviceMessage deviceMessage;
  String messageString;
  
  this->buildMessage(data, type, deviceMessage);
  return this->sendMessage(deviceMessage);
}


int DeviceSerial::sendMessage(DeviceMessage deviceMessage)
{
  String messageString;
  this->messageToString(deviceMessage, messageString);
  return Serial.print(messageString);
}


boolean DeviceSerial::available(unsigned int time)
{
  this->debug("Start DeviceSerial::available()");
  if (!this->hasMessage) {
    // No message currently available, look in data stream for one
    this->lookForMessage(time);
  }
  this->debug("Finish DeviceSerial::available(), result: ", this->hasMessage);
  return this->hasMessage;
}

boolean DeviceSerial::available()
{
  return this->available(DEVICE_SERIAL_DEFAULT_TIMEOUT);
}

boolean DeviceSerial::receiveMessage(DeviceMessage &message, unsigned int time)
{
  if (this->available(time)) {
    this->cloneMessage(this->currentMessage, message);
    this->hasMessage = false;
    return true;
  }
  else {
    return false;
  }
}

boolean DeviceSerial::receiveMessage(DeviceMessage &message)
{
  return this->receiveMessage(message, DEVICE_SERIAL_DEFAULT_TIMEOUT);
}


void DeviceSerial::lookForMessage(unsigned int time)
{
  this->debug("Start DeviceSerial::lookForMessage()");
  Serial.setTimeout(time);
  
  // TODO: Improve by check if there's any available and add to buffer without locking up program
  int bytesRead;
  bytesRead = Serial.readBytesUntil((byte)MESSAGE_END, this->buffer, MESSAGE_MAX_SIZE);
  this->buffer[bytesRead] = (char) 0;
  
  this->debug("Current this->buffer: ", this->buffer);
  
  String bufferString = String(this->buffer);
  
  if (bytesRead == 0) {
    // No message end, clear out currentMessage
    this->hasMessage = false;
    
    this->debug("Start DeviceSerial::lookForMessage() - No Message In Stream");
    return;
  }
  else
  {
     this->hasMessage = this->stringToMessage(bufferString, this->currentMessage);
  }
  this->debug(String("Start DeviceSerial::lookForMessage() - this->hasMessage: ") + this->hasMessage);
  return;
}


void DeviceSerial::debug(String message)
{
  #ifdef DEVICE_SERIAL_DEBUG
  this->send(message, "debug-DeviceSerial");
  #endif DEVICE_SERIAL_DEBUG
}

void DeviceSerial::debug(char charMessage[])
{
  this->debug(String(charMessage));
}

void DeviceSerial::debug(char charMessage1[], char charMessage2[])
{
  this->debug(String(charMessage1) + charMessage2);
}

void DeviceSerial::debug(char charMessage1[], String message2)
{
  this->debug(String(charMessage1) + message2);
}

void DeviceSerial::debug(char charMessage1[], boolean message2)
{
  if (message2) {
    this->debug(charMessage1, "true");
  }
  else {
    this->debug(charMessage1, "false");
  }
}
