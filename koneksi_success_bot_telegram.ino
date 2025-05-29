#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <time.h>

const char* ssid = "TP-Link_39EA";
const char* password = "64123127";

// Ganti dua poin di bawah ini yang sesuai
#define BOTtoken "7706xxxx:xxxxxxxxxx" 
#define CHAT_ID "886xxxx"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi terhubung");

  // Wajib sinkron waktu agar HTTPS ke Telegram bisa jalan
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("Sinkronisasi waktu...");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("✓");

  client.setInsecure();  // Lewati verifikasi sertifikat SSL

  // Tes kirim pesan
  Serial.println("Mengirim pesan...");
  bool sukses = bot.sendMessage(CHAT_ID, "Halo! Ini pesan dari ESP32 🚀", "");
  if (sukses) {
    Serial.println("✅ Pesan berhasil dikirim!");
  } else {
    Serial.println("❌ Gagal kirim pesan. Cek TOKEN atau CHAT_ID!");
  }
}

void loop() {}
