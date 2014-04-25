#include "Arduino.h";
#include "Device.h";
#include "DeviceMessage.h";
#include "DeviceSerial.h";

// Class constructor
Device::Device(unsigned int deviceId)
{
  this->deviceId = deviceId;
}

// TODO: Add targetDeviceId
void Device::buildMessage(String data, String type, DeviceMessage &deviceMessage)
{
  deviceMessage = DeviceMessage();
  // Start with device id
  deviceMessage.deviceId = this->deviceId;
  
  // Add then increment the message count as the message id
  deviceMessage.messageId = this->messageCount;
  this->messageCount++;
  
  // Add the type, if any
  deviceMessage.type = type;
  
  // Then add the data
  deviceMessage.data = data;
  
}

void Device::messageToString(DeviceMessage message, String &messageString)
{
  messageString = String();
  
  // Start with device_id
  messageString.concat(message.deviceId);
  messageString.concat(MESSAGE_DELIM);
  
  // Add message id
  messageString.concat(message.messageId);
  messageString.concat(MESSAGE_DELIM);
  
  // TODO: Add targetDeviceId
  
  // Add the type
  messageString.concat(message.type);
  messageString.concat(MESSAGE_DELIM);
  
  // Add the data and end the string
  messageString.concat(message.data);
  messageString.concat(MESSAGE_END);
}


boolean Device::stringToMessage(String messageString, DeviceMessage &message)
{
  this->debug("Start Device::StringToMessage()");
  this->debug("String to extract message from: ", messageString);
  message = DeviceMessage();
  
  String tmpString;
  
  // Extract deviceId
  int delimIndexDeviceId = messageString.indexOf(MESSAGE_DELIM);
  if (delimIndexDeviceId < 1) {
    // Can't find delim after deviceId, or there is no deviceId to get from string
    return false;
  }
  tmpString = messageString.substring(0, delimIndexDeviceId);
  this->debug("Extracted deviceId: ", tmpString);
  message.deviceId = tmpString.toInt();
  
  // Extract messageId
  int delimIndexMessageId = messageString.indexOf(MESSAGE_DELIM, delimIndexDeviceId+1);
  if (delimIndexMessageId < delimIndexDeviceId+1) {
    // Can't find delim after messageId, or there is no messageId to get from string
    return false;
  }
  tmpString = messageString.substring(delimIndexDeviceId+1, delimIndexMessageId);
  this->debug("Extracted messageId: ", tmpString);
  message.messageId = tmpString.toInt();
  
  // TODO: Add in targetDeviceId
  
  // Extract type
  int delimIndexType = messageString.indexOf(MESSAGE_DELIM, delimIndexMessageId+1);
  if (delimIndexType < 0) {
    // Can't find delim after deviceId
    return false;
  }
  String type = messageString.substring(delimIndexMessageId+1, delimIndexType);
  this->debug("Extracted type: ", type);
  message.type = type;
  
  // Extract data
  // Message end is optional.
  int messageEndIndex = messageString.indexOf(MESSAGE_END, delimIndexType+1);
  String data;
  if (messageEndIndex < 0) {
    // No message end to cut off, just extract to the end of the string
    data = messageString.substring(delimIndexType+1);
  }
  else if (messageEndIndex > delimIndexType) {
    // We have end message character.  Stop string just before it.
    data = messageString.substring(delimIndexType+1, messageEndIndex);
  }
  else {
    // This is strange, how can the messageEndIndex come before the type's delimiter?  Something is wrong
    return false;
  }
  this->debug("Extracted data: ", data);
  message.data = data;
  
  this->debug("Finished Device::StringToMessage(): Successfully extracted message from string");
  
  return true;
}


void Device::cloneMessage(DeviceMessage sourceMessage, DeviceMessage &targetMessage)
{
  targetMessage = DeviceMessage();
  targetMessage.deviceId = sourceMessage.deviceId;
  targetMessage.messageId = sourceMessage.messageId;
  targetMessage.targetDeviceId = sourceMessage.targetDeviceId;
  targetMessage.type = String(sourceMessage.type);
  targetMessage.data = String(sourceMessage.data);
}




void Device::debug(String message)
{
  #ifdef DEVICE_DEBUG
  // Hardcoded string for now.  Have this class accept a deviceSerial object to send logs to.
  Serial.print(String("0|0|debug-Device|")+message+"\n");
  #endif DEVICE_DEBUG
}

void Device::debug(char charMessage[])
{
  this->debug(String(charMessage));
}

void Device::debug(char charMessage1[], char charMessage2[])
{
  this->debug(String(charMessage1) + charMessage2);
}

void Device::debug(char charMessage1[], String message2)
{
  this->debug(String(charMessage1) + message2);
}

void Device::debug(char charMessage1[], boolean message2)
{
  if (message2) {
    this->debug(charMessage1, "true");
  }
  else {
    this->debug(charMessage1, "false");
  }
}
