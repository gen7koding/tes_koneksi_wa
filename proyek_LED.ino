void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  Serial.begin(9600);
  Serial.println("Latihan pertama");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(12, HIGH);
  //digitalWrite(13, HIGH);
  digitalWrite(14, LOW);
  delay(1000); // satuan millisekon 
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(14, HIGH);
  delay(1000); // satuan millisekon 

}