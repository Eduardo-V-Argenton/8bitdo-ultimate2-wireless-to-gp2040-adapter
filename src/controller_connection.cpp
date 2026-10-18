#include <Arduino.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include "8bitdo_ultimate2_wireless_map.hpp"
#include "controller_connection.hpp"
#include "debug.hpp"

bool controller_found = false;
BLEAdvertisedDevice*controller = nullptr;
BLEClient* client = nullptr;
GamepadState gamepad;
volatile bool controller_disconnected = false;

// The notify callback runs in the BLE task, loop() runs in the Arduino task.
static uint8_t report[REPORT_SIZE];
static bool newReport = false;
static portMUX_TYPE reportMux = portMUX_INITIALIZER_UNLOCKED;

void notifyCallback(BLERemoteCharacteristic* characteristic, uint8_t* data,
                    size_t length, bool isNotify) 
{
  // Ignore reports too short to be the gamepad report.
  if(length < REPORT_MIN_SIZE)
  {
    return;
  }
  if(length > REPORT_SIZE)
  {
    length = REPORT_SIZE;
  }

  portENTER_CRITICAL(&reportMux);
  memset(report, 0, REPORT_SIZE);
  memcpy(report, data, length);
  newReport = true;
  portEXIT_CRITICAL(&reportMux);
}

bool take_report(uint8_t* out)
{
  bool has_report = false;

  portENTER_CRITICAL(&reportMux);
  if(newReport)
  {
    memcpy(out, report, REPORT_SIZE);
    newReport = false;
    has_report = true;
  }
  portEXIT_CRITICAL(&reportMux);

  return has_report;
}

class ClientCallbacks : public BLEClientCallbacks {
  void onConnect(BLEClient* client) override {}

  void onDisconnect(BLEClient* client) override
  {
    controller_disconnected = true;
  }
};

class ScanCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice device) override 
  {
    if(device.haveName()) {
      String name = device.getName().c_str();

      if(name == "8BitDo Ultimate 2 Wireless")
      {
        DEBUG_PRINTLN("8BitDo Ultimate 2 Wireless found");
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
    DEBUG_PRINTLN("Controller not found. Restarting in 3s");
    sleep(3);
    ESP.restart();
  }
}

void connect_controller()
{
  client = BLEDevice::createClient();
  client->setClientCallbacks(new ClientCallbacks());

  if (client->connect(controller)) 
  {
    DEBUG_PRINTLN("Connected");
  }
  else 
  {
    DEBUG_PRINTLN("Failed to connect. Restaring in 3s");
    sleep(3);
    ESP.restart();
  }

  BLEUUID hidUUID((uint16_t)0x1812);
  BLERemoteService* hidService = client->getService(hidUUID);
  if(hidService == nullptr) {
    DEBUG_PRINTLN("ERROR: HID service not found. Restarting in 3s");
    sleep(3);
    ESP.restart();
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