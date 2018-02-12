#pragma once

//
// Created by KEDARUMA FANTASTIC on 2018/01/13.
//

#include <Arduino.h>
#include "WiFiManager.h"

class MyWifiManager : public WiFiManager {
 public:
  MyWifiManager() {}
  virtual ~MyWifiManager() {}

  uint32_t get_blink_interval() { return interval_;}

 private:
  virtual void bindHandler() override;
  const String get_html_root_page_custom_menu_items() override;
  int http_test(String host);
  void handle_custom_setting_from();
  void handle_custom_setting_store();
  void handle_custom_ping_test();
  void handle_custom_wifi_setting_reset();

  String ping_host_ = "http://google.com";
  String ping_result_ = "";
  uint32_t interval_ = 1000;
};
