#include "nfc_driver.h"
#include <Wire.h>
#include <Adafruit_PN532.h>
#include <LittleFS.h>

Adafruit_PN532 nfc(21, 22);

#define MAX_USERS 50
static NFCtag AuthorizedTags[MAX_USERS];
static int UserCount = 0;

/*
  Setup NFC se encarga de inicializar el módulo NFC y cargar los tags autorizados.
*/
void setupNFC() {
  Serial.println("🔍 Iniciando NFC...");
  nfc.begin();
  
  uint32_t version = nfc.getFirmwareVersion();
  if (version) {
    Serial.println("✅ NFC detectado");
  } else {
    Serial.println("❌ NFC no detectado");
  }
  
  nfc.SAMConfig();
  loadAuthorizedTags();
  Serial.println("✅ NFC listo con sistema de autorización");
}

/*
  checkNFCTags verifica si hay un tag NFC presente y valida si está autorizado.
*/
void checkNFCTags() {
  uint8_t uid[7];
  uint8_t uidLength;
  
  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 100)) {
    String uidStr = "";
    for (uint8_t i = 0; i < uidLength; i++) {
      if(uid[i] < 0x10) uidStr += "0";
      uidStr += String(uid[i], HEX);
      uidStr += " ";
    }
    uidStr.trim();
    uidStr.toLowerCase();
    
    Serial.print("🏷️ Tag detectado: ");
    Serial.print(uidStr);
    
    if(isTagAuthorized(uidStr)) {
      Serial.println(" - 🔓 ACCESO CONCEDIDO");
    } else {
      Serial.println(" - 🔐 ACCESO DENEGADO");
    }
  }
}

/*
  isTagAuthorized verifica si el UID del tag está en la lista de autorizados.
*/
bool isTagAuthorized(String uid) {
  Serial.println("🔍 Buscando UID: '");
  Serial.print(uid);
  Serial.println("'");
  
  for(int i = 0; i < UserCount; i++) {
    Serial.println("   Comparando con: '");
    Serial.print(AuthorizedTags[i].uid);
    Serial.println("' - Resultado: ");
    
    if(AuthorizedTags[i].uid == uid && AuthorizedTags[i].authorized) {
      Serial.println("✅ COINCIDENCIA");
      return true;
    } else {
      Serial.println("❌ NO COINCIDE");
    }
  }
  return false;
}

/*
  addAuthorizedTag agrega un nuevo tag autorizado a la lista.
*/
void addAuthorizedTag(String uid, String name, bool authorized) {
  if(UserCount < MAX_USERS) {
    AuthorizedTags[UserCount].uid = uid;
    AuthorizedTags[UserCount].name = name;
    AuthorizedTags[UserCount].authorized = authorized;
    UserCount++;
    saveAuthorizedTag();

    Serial.print("➕ Tag autorizado agregado: ");
    Serial.println(uid);
  }
}

/*
  loadAuthorizedTags carga los tags autorizados desde LittleFS (simulado aquí).
*/
void loadAuthorizedTags() {
  UserCount = 0;
  addAuthorizedTag("c0 e9 e4 5f", "Tu Tag Principal", true);
  Serial.println("=== DEBUG TAGS CARGADOS ===");
  for(int i = 0; i < UserCount; i++) {
    Serial.print("   Tag ");
    Serial.print(i);
    Serial.print(": '");
    Serial.print(AuthorizedTags[i].uid);
    Serial.println("'");
  }
  Serial.println("===========================");
}


void saveAuthorizedTag() {
  // Por ahora solo debug - luego guardaremos en LittleFS
  Serial.println("💾 Tags guardados (simulado)");
}