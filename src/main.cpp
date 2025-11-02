#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

// Crear servidor web estándar
WebServer server(80);

void handleHealth() {
  String response = "{\"status\":\"ok\",\"timestamp\":" + String(millis()) + ",\"free_heap\":" + String(esp_get_free_heap_size()) + "}";
  server.send(200, "application/json", response);
}

void handleInfo() {
  String info = "{";
  info += "\"chip_model\":\"ESP32\",";
  info += "\"free_heap\":" + String(esp_get_free_heap_size()) + ",";
  info += "\"flash_size\":" + String(ESP.getFlashChipSize()) + ",";
  info += "\"wifi_clients\":" + String(WiFi.softAPgetStationNum());
  info += "}";
  server.send(200, "application/json", info);
}

void setup() {
  // Iniciar comunicación serial
  Serial.begin(115200);
  delay(2000);
  
  Serial.println();
  Serial.println("🚀 Iniciando Sistema NFC Access Control...");

  // 1. Montar LittleFS
  Serial.print("📁 Montando LittleFS... ");
  if (!LittleFS.begin(true)) {
    Serial.println("ERROR - Continuando sin LittleFS");
  } else {
    Serial.println("OK");
  }

  // 2. Iniciar WiFi en modo AP
  Serial.print("📡 Iniciando WiFi AP... ");
  if (WiFi.softAP("nfc-access-control", "password123")) {
    Serial.println("OK");
    Serial.print("📶 IP del AP: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("ERROR");
    return;
  }

  // 3. Configurar endpoints
  server.on("/health", handleHealth);
  server.on("/info", handleInfo);
  
  // 4. Iniciar servidor
  server.begin();
  
  Serial.println("✅ Sistema listo!");
  Serial.println("🌐 Endpoints disponibles:");
  Serial.println("   http://" + WiFi.softAPIP().toString() + "/health");
  Serial.println("   http://" + WiFi.softAPIP().toString() + "/info");
  Serial.println("📊 Conéctate al WiFi: nfc-access-control");
  Serial.println("🔑 Password: password123");
}

void loop() {
  // Manejar clientes web
  server.handleClient();
  
  // Mostrar estado cada 30 segundos
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 30000) {
    lastPrint = millis();
    Serial.print("💾 Heap libre: ");
    Serial.print(esp_get_free_heap_size());
    Serial.println(" bytes");
  }
  
  delay(10);
}