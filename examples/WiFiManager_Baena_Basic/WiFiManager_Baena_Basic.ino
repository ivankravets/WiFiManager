//
// Created by KEDARUMA FANTASTIC on 2018/01/13.
//

#include <Arduino.h>
#include "my_wifi_manager.h"

namespace {

// Access point name
// アクセスポイント名
const char ap_name_[] PROGMEM = "MY ESP8266";
// Access point authentication password
// 認証パスワード
const char ap_passwd_[] PROGMEM = "12345678";

MyWifiManager wifi_manager_;

unsigned long last_millis_ = 0;
bool is_led_on_ = false;

} // namespace


void setup()
{
  // Grace to write to flash
  delay(5000);

  Serial.begin(9600);
  Serial.println("\n\n\nhello!!!");

  pinMode(LED_BUILTIN, OUTPUT);

  String ap_name = FPSTR(ap_name_);
  String ap_passwd = FPSTR(ap_passwd_);
  wifi_manager_.startConfigPortalMulti(ap_name.c_str(), ap_passwd.c_str());
}

void loop()
{
  // Always call this member function with setup()
  wifi_manager_.updateConfigPortalMulti();

  if (Serial.available() > 0) {
    String input_str = "";
    while(Serial.available()) {
      input_str.concat(static_cast<char>(Serial.read()));
    }
    Serial.print("Serial input: ");
    Serial.println(input_str);
  }

  unsigned long interval = wifi_manager_.get_blink_interval();
  auto cur_millis = millis();
  auto dt = cur_millis - last_millis_;
  if (dt > interval) {
    last_millis_ = cur_millis;

    is_led_on_ = !is_led_on_;
    if (is_led_on_) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("<<< ON >>>");
    } else {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("<<< OFF >>>");
    }
  }
}
