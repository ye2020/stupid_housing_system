/**
  ****************************** Y.Z.T.****************************************
  * @file       usr_wifi.c/h
  * @brief      用于存放wifi连接和扫码配网的相关函数和类定义
  * @note       none
  * 
  * @author     Y.Z.T
  * @history    2023.9.18
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */

#include <ESP8266HTTPClient.h>    //网页用
#include "usr_wifi.h"
#include "usr_eeprom.h"
#include "usr_clock_time.h"

using namespace std;

usr_wifi_t usr_Wifi;
HTTPClient http;


/**
 * @brief       wifi初始化函数
 * @param[in]   none
 * @retval      
 * @attention   会自动调用上一个连接成功的wifi来连接
 */
void usr_wifi_t::wifi_init(void)
{
  Serial.println("wifi ssid:");
  Serial.println(eepUserSet.wifi_ssid);
  Serial.println("wifi pwd:");
  Serial.println(eepUserSet.wifi_password);

  WiFi.mode(WIFI_OFF);
  usr_Wifi.get_wifi(eepUserSet.wifi_ssid,eepUserSet.wifi_password);        // 从flash中读取


  clock_init();                                                       // NTP时钟初始化
  // if(WiFi.status() != WL_CONNECTED)
  //   usr_Wifi.wifi_smartconfig();
}


/**
 * @brief       wifi连接函数
 * @param[in]   none
 * @retval      
 * @attention   成功连接的话,会输出该网络的ip
 */
void usr_wifi_t::get_wifi(const char* SSID,const char* Password)     //连接 wifi
{ 
  uint8_t i = 0;  //用来判断半分钟内是否联网成功 , 否则提示
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, Password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {   //检测 wifi 连接状态
    delay(500);
    i++;
    Serial.print(".");

    if(i>=20)
    { 
      usr_Wifi.usr_wifi_status = usr_Wifi.wifi_connect_fail;   //表示wifi连接失败
      Serial.println("Failed to connect wifi within 5s ");    // 5s内未成功连接wifi （编码显示问题 用串口输出的话 utf-8 会乱码 ，改GBK的话 显示器乱码 + 注释乱码）

      break;
    }
  }

  if( WiFi.status()  == WL_CONNECTED ) //表示wifi连接成功
  {   
    usr_Wifi.usr_wifi_status = usr_Wifi.wifi_connect_success;
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());


    http.setTimeout(5000);
  }

}


/**
 * @brief       wifi断开
 * @param[in]   none
 * @retval      
 * @attention   
 */
void usr_wifi_t::wifi_disconnect(void)
{
  if( WiFi.status()  == WL_CONNECTED )      // 网络是连接状态的
  {
    WiFi.disconnect(1);
  }
}

// 快速链接wifi, 连接最近一次网络
void usr_wifi_t::wifi_quick_link(void)
{
  eeprom_read();            // 读取eeprom数据
  usr_Wifi.get_wifi(eepUserSet.wifi_ssid,eepUserSet.wifi_password);        // wifi连接
}

// 返回IP地址
IPAddress usr_wifi_t::return_IP_addr(void)
{
  return(WiFi.localIP());
}


// 返回网络名称
String usr_wifi_t::return_SSID(void)
{
  return(WiFi.SSID());
}

// 返回MAC地址
String usr_wifi_t::return_MAC(void)
{
  return(WiFi.macAddress());
}
/**
 * @brief       wifi智能配网连接函数
 * @param[in]   none
 * @retval      
 * @attention   用于扫码配网功能,没连接成功之前会一直等待,没有超时时间
 */
void usr_wifi_t::wifi_smartconfig(void)
{
    Serial.println("WiFi smart_connecting...");
    WiFi.mode(WIFI_STA);
    WiFi.beginSmartConfig();

    if(WiFi.smartConfigDone()){
        usr_Wifi.usr_wifi_status = usr_Wifi.wifi_connect_success;           //连接成功
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        http.setTimeout(5000);
        WiFi.stopSmartConfig();
    }

    while (1)
    {
        Serial.print(".");
        delay(500);                   // wait for a second
        if (WiFi.smartConfigDone())
        {
        Serial.println("SmartConfig Success");
        Serial.printf("SSID:%s\r\n", WiFi.SSID().c_str());
        Serial.printf("PSW:%s\r\n", WiFi.psk().c_str());
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());

        wifi_eeprom(WiFi.SSID().c_str(),WiFi.psk().c_str());                // 将成功连接的wifi到的SSID和pwd 写入flash
        break;
        }
    }

    
    usr_Wifi.get_wifi(WiFi.SSID().c_str(),WiFi.psk().c_str());          // 利用获取到的SSID和psw 进行网络连接
}