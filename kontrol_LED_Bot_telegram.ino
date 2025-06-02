#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "TP-Link_39EA";
const char* password = "xxxxx";

#define BOTtoken "xxxxxxx"
#define CHAT_ID "88xxxxx"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

const int ledPin = 14;

unsigned long lastTimeBotRan;

#include <time.h>

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi terhubung");
  delay(2000);

  configTime(0, 0, "pool.ntp.org", "time.nist.gov"); // sinkron waktu pakai NTP
  Serial.println("Menunggu sinkronisasi waktu...");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {  // tunggu sampai waktu benar
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("\nWaktu sudah sinkron");

  client.setInsecure();

  Serial.println("Mengirim pesan awal...");
  bool ok = bot.sendMessage(CHAT_ID, "Bot aktif! Ketik ON atau OFF", "");
  if (ok) {
    Serial.println("Pesan awal terkirim");
  } else {
    Serial.println("Gagal kirim pesan awal");
  }
}

void loop() {
  if (millis() - lastTimeBotRan > 1000) {
    int n = bot.getUpdates(bot.last_message_received + 1);
    Serial.println("Memeriksa pesan...");
    if (n) {
      for (int i = 0; i < n; i++) {
        String text = bot.messages[i].text;
        Serial.println("Pesan diterima: " + text);
        if (text == "ON") {
          digitalWrite(ledPin, HIGH);
          bot.sendMessage(CHAT_ID, "LED dinyalakan ✅", "");
          Serial.println("LED dinyalakan");
        } else if (text == "OFF") {
          digitalWrite(ledPin, LOW);
          bot.sendMessage(CHAT_ID, "LED dimatikan ❌", "");
          Serial.println("LED dimatikan");
        }
      }
    } else {
      Serial.println("Tidak ada pesan baru");
    }
    lastTimeBotRan = millis();
  }
}
