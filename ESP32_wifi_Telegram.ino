/* Code based on turorial from https://randomnerdtutorials.com/telegram-esp32-motion-detection-arduino/
 * Follow the tutorial for reference
 *  
 */

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <string> 
#include <stdio.h>
#include <string.h>

#include "config/ESP32_wifi_Telegram_config.h"

// Replace with your network credentials
const char* ssid = SSID_;
const char* password = PSW_;

// Initialize telegram bot
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Minutes passed
int mins = 0;
// String variables for the message to be sent
char str[30];
char minsStr[5];
    
void setup() {
  Serial.begin(115200);

  // Base message
  strcpy(str, "Minutes since start: ");

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Defined in the Telegram library
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  bot.sendMessage(CHAT_ID, "Bot started up", "");
}

void loop() {

    // Add minutes passed to the message and send
    itoa(mins, minsStr, 10);
    strcat(str,minsStr);
    bot.sendMessage(CHAT_ID, str, "");
    
    Serial.print("Minutes since start: ");
    Serial.println(mins);
    mins++;
    
    // Remove minutes from message
    strcpy(str, "Minutes since start: ");
    
    delay(60000);
}
