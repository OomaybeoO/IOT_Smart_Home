#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Wire.h>
#include "BME82M131.h"
#include "BM25S2021-1.h"
#define LED1 15
#define LED2 2
#define FAN1 0
#define FAN2 4
// 創建 BME82M131 物件，用於讀取光強度
extern BME82M131 ALS;
// 創建 BM25S2021_1 物件，用於讀取溫度和濕度
extern BM25S2021_1 BMht;

// 定義結構體來存儲感測數據
struct SensorData {
    float lux;
    float humidity;
    float temperature;
};

// 函數原型
void initializeSensors();
SensorData readSensorData();
void ControlDevices(bool led1,bool led2,bool fan1,bool fan2);
#endif // SENSORMANAGER_H
