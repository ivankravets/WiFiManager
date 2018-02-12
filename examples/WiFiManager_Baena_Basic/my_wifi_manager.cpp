//
// Created by KEDARUMA FANTASTIC on 2018/01/13.
//

#include "my_wifi_manager.h"
#include <ESP8266HTTPClient.h>

using namespace wifiman_const;

namespace {

// custom setting form
const char CUSTOM_SETTING_FROM[] PROGMEM = R"HEREDOC(
<form action='/custom_setting_store' method='get'>
  <input type="text" name='interval' placeholder='Blink interval(millisec)' value='{interval}'><br/>
  <input type="submit" onclick="oem()" value="Set blink interval">
</form>

<form action='/custom_setting_ping_test' method='get'>
  <p>Result HTTP Code: {result}</p>
  <input type="text" name='host' placeholder='Host' value='{host}'><br/>
  <input type="submit" onclick="oem()" value="HTTP Test">
</form>

<h2><br><br>View Component Sample</h2>

<h3><br><br>Slider<br></h3>
<input type="range" min="1" max="100" value="50" class="slider" id="myRange">

<h3><br><br>Selector</h3>
<div id="sl">
  <select name="horoscope" size="12">
    <option value="Aries">おひつじ座</option>
    <option value="Taurus">おうし座</option>
    <option value="Gemini">ふたご座</option>
    <option value="Cancer">かに座</option>
    <option value="Leo">しし座</option>
    <option value="Virgo">おとめ座</option>
    <option value="Libra">てんびん座</option>
    <option value="Scorpio">さそり座</option>
    <option value="Saggitarius">いて座</option>
    <option value="Capricorn">やぎ座</option>
    <option value="Aquarius">みずがめ座</option>
    <option value="Pisces">うお座</option>
  </select>
</div>

<!--check box-->
<h3>Check Buttons</h3>
<label class="cb">One
  <input type="checkbox" checked="checked">
  <span class="cm"></span>
</label>
<label class="cb">Two
  <input type="checkbox">
  <span class="cm"></span>
</label>

<label class="cb">Three
  <input type="checkbox">
  <span class="cm"></span>
</label>

<label class="cb">Four
  <input type="checkbox">
  <span class="cm"></span>
</label>

<!--radio button-->
<h3><br>Radio Buttons</h3>
<label class="rb">One
  <input type="radio" checked="checked" name="radio">
  <span class="cm"></span>
</label>
<label class="rb">Two
  <input type="radio" name="radio">
  <span class="cm"></span>
</label>
<label class="rb">Three
  <input type="radio" name="radio">
  <span class="cm"></span>
</label>
<label class="rb">Four
  <input type="radio" name="radio">
  <span class="cm"></span>
</label>
)HEREDOC";

} // namespace

// additional custom menu
const String MyWifiManager::get_html_root_page_custom_menu_items() {
  String menu_item = get_html_menu_item();
  menu_item.replace(FPSTR(FS_SBJ), F("MY DEVICE MENU"));
  menu_item.replace(FPSTR(FS_HR), F("/custom_setting_from"));
  return menu_item;
}

int MyWifiManager::http_test(String host) {
  HTTPClient http;
  http.begin(host);
  auto code = http.GET();
  http.end();
  return code;
}

void MyWifiManager::handle_custom_setting_from() {
  DEBUG_WM(__PRETTY_FUNCTION__);

  String page = get_html_head();
  page += get_html_head_end();

  page += get_html_child_page_header();
  auto title = F("MY DEVICE MENU");
  page.replace(FPSTR(FS_T), title);
  page.replace(FPSTR(FS_TT), title);

  page += FPSTR(CUSTOM_SETTING_FROM);
  page.replace(F("{interval}"), String(interval_));
  page.replace(F("{host}"), ping_host_);
  page.replace(F("{result}"), ping_result_);
  ping_result_ = "";

  page += get_html_end();
  server->sendHeader(FPSTR(FS_CONTENT_LENGTH), String(page.length()));
  server->send(200, FPSTR(FS_TEXT_HTML), page);
}

void MyWifiManager::handle_custom_setting_store() {
  DEBUG_WM(__PRETTY_FUNCTION__);

  interval_ = static_cast<uint32_t>(server->arg(F("interval")).toInt());
  server->sendHeader(FPSTR(FS_LOCATION), F("/custom_setting_from"), true);
  server->send(303, FPSTR(FS_TEXT_PLAIN), "");
}

void MyWifiManager::handle_custom_ping_test() {
  DEBUG_WM(__PRETTY_FUNCTION__);

  ping_host_ = server->arg(F("host"));
  DEBUG_WM(String("ping host = " + ping_host_));
  auto code = http_test(ping_host_);
  ping_result_ = String(code);
  DEBUG_WM("result http code = " + code);

  server->sendHeader(FPSTR(FS_LOCATION), F("/custom_setting_from"), true);
  server->send(303, FPSTR(FS_TEXT_PLAIN), "");
}

void MyWifiManager::handle_custom_wifi_setting_reset() {
  DEBUG_WM(__PRETTY_FUNCTION__);

  resetSettings();
  handleReset();
}

void MyWifiManager::bindHandler() {
  DEBUG_WM(__PRETTY_FUNCTION__);

  WiFiManager::bindHandler();

  // custom handler bind
  server->on("/custom_setting_from", std::bind(&MyWifiManager::handle_custom_setting_from, this));
  server->on("/custom_setting_store", std::bind(&MyWifiManager::handle_custom_setting_store, this));
  server->on("/custom_setting_ping_test", std::bind(&MyWifiManager::handle_custom_ping_test, this));
  server->on("/custom_setting_wifi_setting_reset", std::bind(&MyWifiManager::handle_custom_wifi_setting_reset, this));
}

