#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
ESP8266WiFiMulti WiFiMulti;

void setup(){
  lcd.init();
  lcd.backlight();
  WiFi.begin("имя сети", "пароль");
}

void up(){
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient http;
  http.begin(*client, "https://api.telegram.org/botТОКЕН БОТА/getChatMembersCount?chat_id=@username");
  int httpCode = http.GET();
  String load = http.getString();

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(load);

  int tempCount = root["result"];

  lcd.setCursor(0,0);
  lcd.print("IT-BRO:");
  lcd.print(tempCount);
  lcd.print("sub");
}

void loop() {
  up();
  delay(1000);
}