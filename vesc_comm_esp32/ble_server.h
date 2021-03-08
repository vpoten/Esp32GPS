#ifndef BLE_SERVER_H_
#define BLE_SERVER_H_


#include <BLEDevice.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define BLE_SERVICE_UUID        "cfb9af75-5d63-42e4-956f-600d2b2acc42"
#define BLE_CHARACTERISTIC_UUID "d886b22a-e18f-4840-bd87-64c7dec42257"


//
//  BLE Server wrapper
//
class BleServerWrapper {
  public:
    ~BleServerWrapper();
    void init(std::string deviceName);
    void start();
    void update();

  public:
    // public properties
    bool deviceConnected = false;
    bool oldDeviceConnected = false;

  protected:
    BLEServer* mServer = NULL;
    BLEService *mService = NULL;
    BLECharacteristic* mCharacteristic = NULL;
    BLEAdvertising *mAdvertising = NULL;
    std::string mMessage = "";
};

//
//  Callbacks for VESC BLE server
//
class VescServerCallbacks: public BLEServerCallbacks {
  
    void onConnect(BleServerWrapper* wrapper) {
      wrapper->deviceConnected = true;
      BLEDevice::startAdvertising();
    };

    void onDisconnect(BleServerWrapper* wrapper) {
      wrapper->deviceConnected = false;
    }

};

#endif /* BLE_SERVER_H_ */
