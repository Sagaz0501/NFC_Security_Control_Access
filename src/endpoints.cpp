#include "endpoints.h"
#include "nfc_driver.h"
#include <ArduinoJson.h>

extern WebServer server;

// Variable para compartir UID escaneado entre loops
String lastScannedUID = "";

void setupNFCEndpoints(WebServer &server) {
  server.on("/nfc/add", HTTP_POST, handleAddTag);
  server.on("/nfc/list", HTTP_GET, handleListTags);
  server.on("/nfc/scan", HTTP_GET, handleScanTag);
  server.on("/nfc/remove", HTTP_POST, handleRemoveTag);

  Serial.println("NFC endpoints configurados.");
  Serial.println("Endpoints:");
  Serial.println("   /nfc/add  [POST] - Agregar tag autorizado");
  Serial.println("   /nfc/list [GET]  - Listar tags autorizados");
  Serial.println("   /nfc/scan [GET]  - Escanear tag NFC");
}

void handleAddTag() {
  if (server.hasArg("plain")) {
    String body = server.arg("plain");
    
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, body);
    
    if (error) {
      server.send(400, "application/json", "{\"error\":\"JSON inválido\"}");
      return;
    }
    
    String uid = doc["uid"] | "";
    String name = doc["name"] | "Sin nombre";
    bool authorized = doc["authorized"] | true; // ← AGREGAR ESTE PARÁMETRO
    
    if (uid == "") {
      server.send(400, "application/json", "{\"error\":\"UID requerido\"}");
      return;
    }
    
    // Agregar tag al sistema CON 3 PARÁMETROS
    addAuthorizedTag(uid, name, authorized); // ← authorized incluido
    
    server.send(200, "application/json", 
      "{\"status\":\"Tag agregado\",\"uid\":\"" + uid + 
      "\",\"authorized\":" + (authorized ? "true" : "false") + "}");
  } else {
    server.send(400, "application/json", "{\"error\":\"Body requerido\"}");
  }
}

void handleListTags() {
  JsonDocument doc; // ← CAMBIAR de DynamicJsonDocument
  JsonArray tags = doc["tags"].to<JsonArray>(); // ← FORMA ACTUALIZADA
  
  // Obtener tags autorizados (necesitamos hacer esta función accesible)
  // Por ahora simulamos
  tags.add("c0 e9 e4 5f - Tag Principal");
  tags.add("04 5a 3b 8c - Tag Backup");
  
  String response;
  serializeJson(doc, response);
  server.send(200, "application/json", response);
}

void handleScanTag() {
  // Escanear tag NFC (esto necesita coordinación con el loop principal)
  if (lastScannedUID != "") {
    server.send(200, "application/json", "{\"uid\":\"" + lastScannedUID + "\"}");
    lastScannedUID = ""; // Resetear después de enviar
  } else {
    server.send(404, "application/json", "{\"error\":\"No se detectó tag\"}");
  }
}

void handleRemoveTag() {
  if (server.hasArg("plain")) {
    String body = server.arg("plain");
    
    JsonDocument doc; // ← CAMBIAR de DynamicJsonDocument
    DeserializationError error = deserializeJson(doc, body);
    
    if (error) {
      server.send(400, "application/json", "{\"error\":\"JSON inválido\"}");
      return;
    }
    
    String uid = doc["uid"] | "";
    
    if (uid == "") {
      server.send(400, "application/json", "{\"error\":\"UID requerido\"}");
      return;
    }
    
    // Aquí iría la función para remover tag (la implementaremos después)
    server.send(200, "application/json", "{\"status\":\"Tag removido (simulado)\",\"uid\":\"" + uid + "\"}");
  } else {
    server.send(400, "application/json", "{\"error\":\"Body requerido\"}");
  }
}