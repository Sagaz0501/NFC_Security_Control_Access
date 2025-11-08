# 🚀 NFC Access Control System

Sistema de control de acceso con ESP32 + PN532 NFC con persistencia en LittleFS y API REST.

## 📋 Estado Actual - Semana 3 ✅

### ✅ **Funcionalidades Implementadas:**
- **ESP32 WiFi AP** (`nfc-access-control`)
- **Sistema NFC** con módulo PN532 (I2C)
- **Persistencia** de tags en LittleFS
- **API REST** para gestión remota
- **Sistema de autorización** en tiempo real

### 🌐 **Endpoints Disponibles:**

#### `POST /nfc/add`
Agrega un nuevo tag autorizado
```json
{
  "uid": "c0 e9 e4 5f",
  "name": "Nombre del tag",
  "authorized": true
}
GET /nfc/list
Lista todos los tags autorizados

GET /nfc/scan
Escanea y devuelve UID del tag presente

GET /health
Estado del sistema

json
{
  "status": "ok",
  "timestamp": 12345,
  "free_heap": 295840
}
🔌 Configuración Hardware
Conexiones PN532:
text
VCC  → 3.3V
GND  → GND
SDA  → GPIO 21
SCL  → GPIO 22
Switches PN532: Modo I2C
🛠️ Uso Básico
Conectar al WiFi: nfc-access-control (pass: password123)

Agregar tags via API:

'''
curl -X POST http://192.168.4.1/nfc/add \
  -H "Content-Type: application/json" \
  -d '{"uid":"c0 e9 e4 5f", "name":"Mi Tag", "authorized":true}'
Los tags persisten después de reinicios
'''

Sistema valida acceso en tiempo real

📁 Estructura del Proyecto
text
src/
├── main.cpp          (Configuración principal + WiFi)
├── nfc_driver.cpp    (Control NFC + persistencia)
└── endpoints.cpp     (API REST)

include/
├── nfc_driver.h
└── endpoints.h

data/                 (Archivos para LittleFS)
🔄 Flujo de Persistencia
Tags se guardan en /config/authorized_tags.txt

Al reiniciar se cargan automáticamente

Agregar via API actualiza archivo y memoria

Validación en tiempo real contra lista en memoria

🚀 Próximos Pasos
Interfaz web para gestión

Logs de acceso con timestamp

Sistema de roles y permisos

Backup/restore de configuración

📅 Última actualización: Noviembre 2024
🔗 Repositorio: https://github.com/Sagaz0501/NFC_Security_Control_Access

text

**¿Quieres que agregue algo más o lo actualizamos así?**