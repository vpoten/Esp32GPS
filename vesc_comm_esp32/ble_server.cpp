#include <Arduino.h>
#include <BLE2902.h>

#include "ble_server.h"


void BleServerWrapper::init(std::string deviceName) {
  // Create the BLE Device
  BLEDevice::init(deviceName);

  // Create the BLE Server
  mServer = BLEDevice::createServer();
  mServer->setCallbacks(new VescServerCallbacks());

  // Create the BLE Service
  mService = mServer->createService(BLE_SERVICE_UUID);

  // Create a BLE Characteristic
  mCharacteristic = mService->createCharacteristic(
                      BLE_CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );

  // Create a BLE Descriptor
  mCharacteristic->addDescriptor(new BLE2902());
}

void BleServerWrapper::start() {
  // Start the service
  mService->start();

  // Start advertising
  mAdvertising = BLEDevice::getAdvertising();
  mAdvertising->addServiceUUID(BLE_SERVICE_UUID);
  mAdvertising->setScanResponse(false);
  mAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
}

void BleServerWrapper::update() {
  // notify changed value
  if (this->deviceConnected) {
    // TODO update characteristic here
    // mCharacteristic->setValue((uint8_t*)&value, 4);
    mCharacteristic->notify();
    delay(10); // bluetooth stack will go into congestion, if too many packets are sent
  }
  // disconnecting
  if (!this->deviceConnected && this->oldDeviceConnected) {
    delay(500); // give the bluetooth stack the chance to get things ready
    mServer->startAdvertising(); // restart advertising
    Serial.println("start advertising");
    this->oldDeviceConnected = this->deviceConnected;
  }
  // connecting
  if (this->deviceConnected && !this->oldDeviceConnected) {
    // do stuff here on connecting
    this->oldDeviceConnected = this->deviceConnected;
  }
}
