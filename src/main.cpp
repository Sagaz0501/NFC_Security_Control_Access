// ===== LED-ONLY TEST MAIN =====
// (ANTES) Comentado todo lo que no sea LEDs:
// #include <WiFi.h>
// #include <WebServer.h>
// #include <nfc_driver.h>
// #include <littleFS.h>
// #include <endpoints.h>

#include <Arduino.h>
#include <led_control.h>

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("=== LED-ONLY TEST ===");

  // Inicializar y secuencia de arranque
  led_setup();
  led_booting();
}

void loop() {
  // Ciclo de prueba simple para verificar funciones:
  delay(1000);
  led_detection();   // Verde parpadea 3 veces
  delay(600);
  led_denied();      // Rojo parpadea 3 veces
  delay(600);
  led_granted();     // Verde ON por 3s
  delay(1200);
}
