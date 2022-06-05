/*
 * Project BlueToothGetDistance
 * Description: Testing Getting Distance Info over Bluetooth
 * Author: Jake
 * Date: 20/05/22
 */

const pin_t RED_LED = D12;
const pin_t YELLOW_LED = D11;
const pin_t GREEN_LED = D10;

//Unique Identifiers for other boards to connnect to
const char* serviceUuid = "58aac0a2-e777-4284-b52f-c1cdb581f325";
const char* characteristicUuid = "7df1f693-89c2-4c4c-a0ea-b0ca4ad050ee";
String dataRecieved;
int lightControl;

//Handles Bluetooth Low Energy Callbacks
static void OnDataRecieved(const uint8_t* data, size_t len, const BlePeerDevice& peer, void* context)
{
  dataRecieved = int(data[0]);
  lightControl = int(data[0]);

//Tells which light to turn on
  if (lightControl == 0)
  {
    digitalWrite(RED_LED, HIGH);
    delay(1s);
    digitalWrite(RED_LED, LOW);
  } else if (lightControl == 1)
  {
    digitalWrite(YELLOW_LED, HIGH);
    delay(1s);
    digitalWrite(YELLOW_LED, LOW);
  } else if (lightControl == 2)
  {
    digitalWrite(GREEN_LED, HIGH);
    delay(1s);
    digitalWrite(GREEN_LED, LOW);
  }
  
}


void setup() {
  //Starts Up Service & Sets/Starts Characteristic
  BleUuid distanceService(serviceUuid);
  BleCharacteristic distanceinfoCharacteristic("distance", BleCharacteristicProperty::WRITE_WO_RSP, characteristicUuid, serviceUuid, OnDataRecieved, (void*)characteristicUuid);

  BLE.addCharacteristic(distanceinfoCharacteristic);

  //Advertising data
  BleAdvertisingData advData;
  advData.appendServiceUUID(distanceService);
  BLE.advertise(&advData);

//Sets LED's
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop() {
Particle.publish("data", dataRecieved);
delay(2000);
}
