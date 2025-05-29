#include <Wire.h>
#include <MPU9250.h>
#include <esp_now.h>
#include <WiFi.h>

MPU9250 mpu;
float yaw = 0, roll = 0, gyroBias = 0;
unsigned long lastUpdate = 0, biasStartTime = 0;
bool biasDone = false;

const unsigned long biasDuration = 5000;
const float yawThreshold = 0.3;

typedef struct 
{
  float roll;
  float yaw;
} struct_message;

struct_message dataToSend;
uint8_t receiverMAC[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA}; //Mac Adress of the receiver ESP32

void setup() 
{

  Serial.begin(115200);
  Wire.begin();

  if (!mpu.setup(0x68)) 
  {
    Serial.println("MPU9250 not found");
    while (true);
  }

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) 
  {
    Serial.println("ESP-NOW init failed");
    while (true);
  }

  esp_now_peer_info_t peer{};
  memcpy(peer.peer_addr, receiverMAC, 6);
  peer.channel = 0;
  peer.encrypt = false;
  esp_now_add_peer(&peer);

  lastUpdate = biasStartTime = millis();
  Serial.println("Ready");
}

void loop() 
{
  if (!mpu.update()) return;

  unsigned long now = millis();
  float dt = (now - lastUpdate) / 1000.0;
  lastUpdate = now;

  roll = atan2(mpu.getAccY(), mpu.getAccZ()) * 180.0 / PI;
  float gz = mpu.getGyroZ();

  if (!biasDone) 
  {
    gyroBias += gz;
    if (now - biasStartTime >= biasDuration) 
    {
      gyroBias /= (biasDuration / 10);  
      biasDone = true;
      Serial.println("Bias ready");
    }
    return;
  }

  float newYaw = yaw + ((gz - gyroBias) * dt);
  if (abs(newYaw - yaw) > yawThreshold) yaw = newYaw;
  if (yaw > 180) yaw -= 360;
  if (yaw < -180) yaw += 360;

  dataToSend.roll = roll;
  dataToSend.yaw = yaw;

  if (esp_now_send(receiverMAC, (uint8_t *)&dataToSend, sizeof(dataToSend)) == ESP_OK) 
  {
    Serial.printf("Sent -> Roll: %.2f | Yaw: %.2f\n", roll, yaw);
  } 
  else 
  {
    Serial.println("Send failed");
  }

  delay(50);
}
