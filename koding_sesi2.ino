#define GAS_SENSOR_PIN A0      // Sensor MQ-2 di pin A0
#define BUZZER_PIN 14          // Buzzer di GPIO14 (D5)
#define LED_MERAH 5            // LED merah di GPIO5 (D1)
#define LED_HIJAU 4            // LED hijau di GPIO4 (D2)

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);

  // Tes awal buzzer
  digitalWrite(BUZZER_PIN, HIGH);
  delay(500);
  digitalWrite(BUZZER_PIN, LOW);

  // Pemanasan sensor gas selama 10 detik
  Serial.println("Memanaskan sensor gas (10 detik)...");
  delay(10000);
  Serial.println("Mulai monitoring gas...");
}

void loop() {
  int gasValue = analogRead(GAS_SENSOR_PIN);
  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  if (gasValue > 900) {  // Ganti threshold sesuai kebutuhan
    // Kondisi bahaya
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(200);
      digitalWrite(BUZZER_PIN, LOW);
      delay(200);
    }

    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_HIJAU, LOW);

    Serial.println("🚨 Gas Terdeteksi!");
  } else {
    // Kondisi aman
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_HIJAU, HIGH);

    Serial.println("✅ Gas Aman");
  }

  delay(1000); // Delay 1 detik antar pembacaan
}