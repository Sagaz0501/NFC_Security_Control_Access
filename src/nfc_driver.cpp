#include "nfc_driver.h"
#include <Wire.h>
#include <Adafruit_PN532.h>
#include <LittleFS.h>
#include "littleFS.h"

Adafruit_PN532 nfc(21, 22);

#define MAX_USERS 50
static NFCtag AuthorizedTags[MAX_USERS];
static int UserCount = 0;

/*
  Setup NFC se encarga de inicializar el módulo NFC y cargar los tags autorizados.
*/
void setupNFC() {
  // Crear carpeta config si no existe
  if (!LittleFS.exists("/config")) {
    createDir(LittleFS, "/config");
    Serial.println("📁 Carpeta /config creada");
  }
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
  // 1. Crear carpeta config si no existe
  if(!LittleFS.exists("/config")) {
    createDir(LittleFS, "/config");
  }

  // 2. Si no existe archivo, CREARLO VACÍO - NO con tags manuales
  if (!LittleFS.exists("/config/authorized_tags.txt")) {
    Serial.println("📝 Creando archivo de tags vacío...");
    writeFile(LittleFS, "/config/authorized_tags.txt", "");
    UserCount = 0;
    Serial.println("✅ Archivo vacío creado - Usa /nfc/add para agregar tags");
    return;
  }

  // 3. SOLO LEER archivo existente - NO crear tags manuales
  File file = LittleFS.open("/config/authorized_tags.txt", "r");
  UserCount = 0;
  
  while(file.available() && UserCount < MAX_USERS) {
    String line = file.readStringUntil('\n');
    line.trim();
    
    if(line.length() > 0) {
      int comma1 = line.indexOf(',');
      int comma2 = line.indexOf(',', comma1 + 1);
      
      if(comma1 > 0 && comma2 > comma1) {
        String uid = line.substring(0, comma1);
        String name = line.substring(comma1 + 1, comma2);
        String authorizedStr = line.substring(comma2 + 1);
        bool authorized = (authorizedStr == "true");
        
        // Agregar tag leído del archivo
        addAuthorizedTag(uid, name, authorized);
      }
    }
  }
  file.close();
  
  Serial.print("✅ ");
  Serial.print(UserCount);
  Serial.println(" tags cargados desde archivo");
}


void saveAuthorizedTag() {  // ← O cambiar declaración a saveAuthorizedTags()
    String content = "";
    for(int i = 0; i < UserCount; i++) {
        content += AuthorizedTags[i].uid + "," + 
                   AuthorizedTags[i].name + "," +
                   (AuthorizedTags[i].authorized ? "true" : "false") + "\n";
    }
    writeFile(LittleFS, "/config/authorized_tags.txt", content.c_str());  // ← MISMA RUTA
}
