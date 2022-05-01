#include <ArduinoBLE.h>
#include "servomoottori.h"
#include "ldr.h"

#include "NRF52_MBED_TimerInterrupt.h"
#define TIMER0_INTERVAL_MS        1000

NRF52_MBED_Timer ITimer0(NRF_TIMER_3);

BLEService solarService("f1a5e96f-31c1-460b-ab00-ed2dd96288d7");
BLEByteCharacteristic voltageCharacteristic("e551fc6e-c4cf-4d11-a29e-4e0f26487a2f", BLERead | BLENotify);
BLEByteCharacteristic batteryCharacteristic("3e4c8036-aa1d-4787-aff7-2a39ac09d452", BLERead | BLENotify);
BLEByteCharacteristic currentAngleCharacteristic("b03043b4-a186-4eb8-b8cf-646ad1a466e1", BLERead | BLENotify);
BLEShortCharacteristic newAngleCharacteristic("e6492961-aec3-4899-b840-abd7d67708e3", BLERead | BLEWrite | BLENotify);
BLEByteCharacteristic manualModeCharacteristic("13b9ad02-6db2-4bc9-88d7-1d8a3a56f9ab", BLERead | BLEWrite | BLENotify);

char state = 'b';
char bluetoothState = 'd';
int panelValue = analogRead(A0);
int batteryValue = analogRead(A1);

void TimerHandler0(){  
  state = 'm';
}

class mainProgram{
  private:
    LDR ldr;
    Servomoottori moottori;
    float panelVoltage = 0;
    float batteryVoltage = 0;
  public:
  mainProgram(){
  };
  void setup(){
    //run all the objects setups here
    ldr.beginLDR();
    moottori.beginServo();
  }
  void measureAndRotate(){
    //measure LDR and rotate if necessary and set timer interrupt
    ldr.readLDR();
    if (ldr.direction == "center"){
      state = 'w';
      ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 10000, TimerHandler0);
      if (bluetoothState == 'e'){
        state = 'l';
      }
    }
    else if (moottori.curPos == 165 && ldr.direction == "left"){
      state = 'w';
      ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 10000, TimerHandler0);
      if (bluetoothState == 'e'){
        state = 'l';
      }
    }
    else if (moottori.curPos == 15 && ldr.direction == "right"){
      state = 'w';
      ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 10000, TimerHandler0);
      if (bluetoothState == 'e'){
        state = 'l';
      }   
    }
    else{
      moottori.moveServo(ldr.direction);
    }
  }
  void bluetoothOn(){
    //send panelvoltage, battery, current angle to the Android app
    float panelVoltage = calculateVoltage(panelValue, 2.33);
    panelVoltage = roundDecimals(panelVoltage);
    float batteryVoltage = calculateVoltage(batteryValue, 1.66);
    batteryVoltage = roundDecimals(batteryVoltage);
    updateValues(panelVoltage, batteryVoltage, moottori.curPos);
  }
  float calculateVoltage(int value, float multiplier){
    return (3.3/1023)*value*multiplier;
  }
  int roundDecimals(float value){
    float temp = value*10;
    int temp2 = temp;
    return temp2;
  }
  void setNewAngle(int angle){
    //set servo to new angle with manual command
    moottori.setServo(angle);
  }

  void updateValues(float voltage, float battery, int currentAngle){
  voltageCharacteristic.writeValue(voltage);
  batteryCharacteristic.writeValue(battery);
  currentAngleCharacteristic.writeValue(currentAngle);
  } 
};

mainProgram mainP;

void bleConnected(BLEDevice central){
  //Bluetooth connected event
  state = 'l';
  bluetoothState = 'e';
}

void bleDisconnected(BLEDevice central) {
  //Bluetooth disconnected event
  state = 'm';
  bluetoothState = 'd';
}

void getManualMode(BLEDevice central, BLECharacteristic characteristic){
  //manual mode enabled or disabled in the app event
  byte value = 0;
  manualModeCharacteristic.readValue(value);
  if (value == 1){
    ITimer0.detachInterrupt();
    state = 'n';
  }
  if (value == 0){
    ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 10000, TimerHandler0);
    state = 'l';
  }
}

void getNewAngle(BLEDevice central, BLECharacteristic characteristic){
  //new angle given in manual mode event
  short value = 0;
  newAngleCharacteristic.readValue(value);
  int intValue;
  intValue = (int) value;
  mainP.setNewAngle(intValue);
}

void setup() {
  //setup all the Bluetooth settings
  BLE.begin();

  //set advertised local name and service UUID:
  BLE.setLocalName("SolarTracker");
  BLE.setAdvertisedService(solarService);

  //add the characteristic to the service
  solarService.addCharacteristic(voltageCharacteristic);
  solarService.addCharacteristic(batteryCharacteristic);
  solarService.addCharacteristic(currentAngleCharacteristic);
  solarService.addCharacteristic(newAngleCharacteristic);
  solarService.addCharacteristic(manualModeCharacteristic);

  //add service
  BLE.addService(solarService);

  //set event handlers
  BLE.setEventHandler(BLEConnected, bleConnected);
  BLE.setEventHandler(BLEDisconnected, bleDisconnected);
  manualModeCharacteristic.setEventHandler(BLEWritten, getManualMode);
  newAngleCharacteristic.setEventHandler(BLEWritten, getNewAngle);

  //set the initial value for the characeristic:
  voltageCharacteristic.writeValue(0);
  batteryCharacteristic.writeValue(0);
  currentAngleCharacteristic.writeValue(90);
  manualModeCharacteristic.writeValue(0);
  newAngleCharacteristic.writeValue(90);

  //start advertising
  BLE.advertise();
  BLE.poll();
}

void loop() {
  panelValue = analogRead(A0);
  batteryValue = analogRead(A1);
  switch (state){
    case 'b': // boot
    mainP.setup();
    state = 'm';
    break;
    case 'w': // waiting
    break;
    case 'm': // measure and rotate
    mainP.measureAndRotate();
    break;
    case 'l': // bluetooth on
    mainP.bluetoothOn();
    break;
    case 'n': // manual mode
    mainP.bluetoothOn();
    break;
  }
  BLE.poll();
}
