#include <Arduino.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include "8bitdo_ultimate2_wireless_map.hpp"
#include "controller_connection.hpp"

BLEScan* scan = nullptr;
bool controller_found = false;
BLEAdvertisedDevice*controller = nullptr;
BLEClient* client = nullptr;
GamepadState gamepad;
uint8_t report[33];
bool newReport;

void notifyCallback(BLERemoteCharacteristic* characteristic, uint8_t* data,
                    size_t length, bool isNotify) 
{
  memcpy(report, data, length);
  newReport = true;
}

class ScanCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice device) override 
  {
    if(device.haveName()) {
      String name = device.getName().c_str();

      if(name == "8BitDo Ultimate 2 Wireless")
      {
        Serial.println("8BitDo Ultimate 2 Wireless found");
        controller_found = true;
        controller = new BLEAdvertisedDevice(device);

        BLEDevice::getScan()->stop();
      }
    }
  }
};

void set_ble_find_controller()
{
  BLEScan* scan = BLEDevice::getScan();

  scan->setAdvertisedDeviceCallbacks(new ScanCallbacks());

  scan->setActiveScan(true);

  scan->start(10, false);

  if(!controller_found)
  {
    Serial.println("Controller not found. Restarting in 3s");
    sleep(3);
    ESP.restart();
  }
}

void connect_controller()
{
  client = BLEDevice::createClient();

  if (client->connect(controller)) 
  {
    Serial.println("Connected");
  }
  else 
  {
    Serial.println("Failed to connect. Restaring in 3s");
    sleep(3);
    ESP.restart();
  }

  BLEUUID hidUUID((uint16_t)0x1812);
  BLERemoteService* hidService = client->getService(hidUUID);
  if(hidService == nullptr) {
    Serial.println("ERROR: HID service not found");
    return;
  } 

  auto* characteristics = hidService->getCharacteristicsByHandle();
  for (auto const& entry : *characteristics) {
    BLERemoteCharacteristic* characteristic = entry.second;

    if (characteristic->getUUID().equals(BLEUUID((uint16_t)0x2A4D))) {
      BLERemoteDescriptor* cccd = characteristic->getDescriptor(BLEUUID((uint16_t)0x2902));
      if(cccd == nullptr){
        continue;
      }
      uint8_t enableNotify[2] = {0x01, 0x00};
      cccd->writeValue(enableNotify, 2, true);
      characteristic->registerForNotify(notifyCallback);
    }
  }
}