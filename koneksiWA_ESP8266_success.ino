#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>   // Tambahan
#include <ESP8266HTTPClient.h>

const char* ssid = "S24+Gen7"; //ganti ssid wifi
const char* pass = "kursusxxxxx"; //ganti password wifi

String nomorAdmin = "62xxxxxxx"; //ganti dengan nomor hp mu  
String apiKeyAdmin = "xxxxxx";   //ganti dengan API key yang diberikan WA

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, pass);
  Serial.print("Menghubungkan WiFi");

  int count = 0;
  while (WiFi.status() != WL_CONNECTED && count < 20) {
    delay(1000);
    Serial.print(".");
    count++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Terhubung ke WiFi!");
    kirimWhatsApp(nomorAdmin, "🚀 Test kirim WA dari ESP8266 sukses (pakai HTTPS)!", apiKeyAdmin);
  } else {
    Serial.println("\n❌ Gagal konek WiFi!");
  }
}

void loop() {
  // kosong
}

void kirimWhatsApp(String nomor_hp, String pesan, String apikey) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();  // <<< Penting: Biar gak cek sertifikat SSL

    HTTPClient https;

    pesan.replace(" ", "%20");
    pesan.replace("!", "%21");

    String url = "https://api.callmebot.com/whatsapp.php?phone=" + nomor_hp +
                 "&text=" + pesan +
                 "&apikey=" + apikey;

    Serial.println("URL WA: " + url);

    if (https.begin(client, url)) {  // Pakai client HTTPS
      int httpCode = https.GET();

      if (httpCode > 0) {
        Serial.println("WA Terkirim ✅: HTTP Code = " + String(httpCode));
        Serial.println("Respon Server: " + https.getString());
      } else {
        Serial.println("❌ Gagal Kirim WA! HTTP Code = " + String(httpCode));
      }

      https.end();
    } else {
      Serial.println("❌ Gagal Mulai HTTPS Connection");
    }

  } else {
    Serial.println("❌ WiFi Belum Terhubung");
  }
}