#include <WiFiNINA.h>
#include <FirebaseESP32.h>  // Include the Firebase library

#define WIFI_SSID "Redmi Note 11"
#define WIFI_PASSWORD "mikul5432"

#define FIREBASE_HOST "arduinocloudfunction-67337-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "AIzaSyBdbIPpV9EPLZMD6rgPSxUZd09ZEYoMDHw"

const int redLED = 5;
const int greenLED = 6;
const int yellowLED = 7;

FirebaseData firebaseData;
FirebaseConfig config;
FirebaseAuth auth;

void setup() {
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Set up Firebase configuration
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Firebase.setString(firebaseData, "/leds/red", "off");
  Firebase.setString(firebaseData, "/leds/green", "off");
  Firebase.setString(firebaseData, "/leds/yellow", "off");
}

void loop() {
  if (Firebase.getString(firebaseData, "/leds/red")) {
    String redState = firebaseData.stringData();
    digitalWrite(redLED, redState == "on" ? HIGH : LOW);
  }
  if (Firebase.getString(firebaseData, "/leds/green")) {
    String greenState = firebaseData.stringData();
    digitalWrite(greenLED, greenState == "on" ? HIGH : LOW);
  }
  if (Firebase.getString(firebaseData, "/leds/yellow")) {
    String yellowState = firebaseData.stringData();
    digitalWrite(yellowLED, yellowState == "on" ? HIGH : LOW);
  }

  delay(100);
}
