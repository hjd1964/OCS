// -----------------------------------------------------------------------------------
// Wifi Web and Cmd servers

#include "../../Common.h"

#if OPERATIONAL_MODE == WIFI

  #include "Wifi.h"

  #if defined(ESP32)
    WebServer www(80);
  #elif defined(ESP8266)
    ESP8266WebServer www(80);
  #endif

  bool accessPointEnabled = AP_ENABLED;
  bool stationEnabled     = STA_ENABLED;
  bool stationDhcpEnabled = STA_DHCP_ENABLED;

  char wifi_sta_ssid[40] = STA_SSID;
  char wifi_sta_pwd[40] = STA_PASSWORD;

  IPAddress wifi_sta_ip = IPAddress STA_IP_ADDR;
  IPAddress wifi_sta_gw = IPAddress STA_GW_ADDR;
  IPAddress wifi_sta_sn = IPAddress STA_SN_MASK;

  char wifi_ap_ssid[40] = AP_SSID;
  char wifi_ap_pwd[40] = AP_PASSWORD;
  byte wifi_ap_ch = AP_CHANNEL;

  IPAddress wifi_ap_ip = IPAddress AP_IP_ADDR;
  IPAddress wifi_ap_gw = IPAddress AP_GW_ADDR;
  IPAddress wifi_ap_sn = IPAddress AP_SN_MASK;

  void wifiInit(void) {
    WiFi.disconnect();
    WiFi.softAPdisconnect(true);
  }

  void wifiStart(void) {
    VF("MSG: WiFi AP Enabled  = "); VL(accessPointEnabled);
    VF("MSG: WiFi Sta Enabled = "); VL(stationEnabled);
    VF("MSG: WiFi Sta DHCP En = "); VL(stationDhcpEnabled);

    VF("MSG: WiFi STA SSID    = "); VL(wifi_sta_ssid);
    VF("MSG: WiFi STA PWD     = "); VL(wifi_sta_pwd);
    VF("MSG: WiFi STA IP      = "); VL(wifi_sta_ip.toString());
    VF("MSG: WiFi STA GATEWAY = "); VL(wifi_sta_gw.toString());
    VF("MSG: WiFi STA SN      = "); VL(wifi_sta_sn.toString());

    VF("MSG: WiFi AP SSID     = "); VL(wifi_ap_ssid);
    VF("MSG: WiFi AP PWD      = "); VL(wifi_ap_pwd);
    VF("MSG: WiFi AP CH       = "); VL(wifi_ap_ch);
    VF("MSG: WiFi AP IP       = "); VL(wifi_ap_ip.toString());
    VF("MSG: WiFi AP GATEWAY  = "); VL(wifi_ap_gw.toString());
    VF("MSG: WiFi AP SN       = "); VL(wifi_ap_sn.toString());

  TryAgain:
    if (accessPointEnabled && !stationEnabled) {
      VLF("MSG: Starting WiFi Soft AP");
      WiFi.softAP(wifi_ap_ssid, wifi_ap_pwd, wifi_ap_ch);
      WiFi.mode(WIFI_AP);
    } else
    if (!accessPointEnabled && stationEnabled) {
      VLF("MSG: Starting WiFi Station");
      WiFi.begin(wifi_sta_ssid, wifi_sta_pwd);
      WiFi.mode(WIFI_STA);
    } else
    if (accessPointEnabled && stationEnabled) {
      VLF("MSG: Starting WiFi Soft AP");
      WiFi.softAP(wifi_ap_ssid, wifi_ap_pwd, wifi_ap_ch);
      VLF("MSG: Starting WiFi Station");
      WiFi.begin(wifi_sta_ssid, wifi_sta_pwd);
      WiFi.mode(WIFI_AP_STA);
    }

    delay(100);
    if (stationEnabled && !stationDhcpEnabled) WiFi.config(wifi_sta_ip, wifi_sta_gw, wifi_sta_sn);
    if (accessPointEnabled) WiFi.softAPConfig(wifi_ap_ip, wifi_ap_gw, wifi_ap_sn);

    // wait for connection in station mode, if it fails fall back to access-point mode
    if (!accessPointEnabled && stationEnabled) {
      for (int i = 0; i < 8; i++) if (WiFi.status() != WL_CONNECTED) delay(1000); else break;
      if (WiFi.status() != WL_CONNECTED) {
        VLF("MSG: Starting WiFi Station, failed");
        WiFi.disconnect(); delay(3000);
        VLF("MSG: Switching to WiFi Soft AP mode");
        stationEnabled = false;
        accessPointEnabled = true;
        goto TryAgain;
      }
    }
  }

#endif
