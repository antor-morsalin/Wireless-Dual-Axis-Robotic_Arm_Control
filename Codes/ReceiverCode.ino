#include <Wire.h>
#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

typedef struct struct_message 
{
  float roll;
  float yaw;
} struct_message;

unsigned long lastUpdate = 0;
struct_message incomingData;
float latestRoll = 0, latestYaw = 0;
bool newDataAvailable = false;

Servo x;
Servo y;


void onDataReceived(const esp_now_recv_info *info, const uint8_t *data, int len) 
{
  if (len == sizeof(struct_message)) 
  {
    memcpy(&incomingData, data, len);
    latestRoll = incomingData.roll;
    latestYaw = incomingData.yaw;
    newDataAvailable = true;
  }
}

void setup() 
{
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) 
  {
    Serial.println("ESP-NOW init failed!");
    while (1);
  }

  esp_now_register_recv_cb(onDataReceived);

  x.attach(13);  // Servo X (Yaw)
  y.attach(14);  // Servo Y (Roll)

  Serial.println("Receiver ready.");
}

void loop() 
{
  
  int rollVal = constrain((int)(latestRoll + 86), 0, 180);
  y.write(180-rollVal);
  delay(50);
  int yawVal = constrain((int)(latestYaw+90), 0, 180);
  x.write(yawVal);
  delay(50);

}
