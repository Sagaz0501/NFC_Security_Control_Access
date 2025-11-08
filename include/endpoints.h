#pragma once
#include <WebServer.h>

// Declaraciones de endpoints NFC
void setupNFCEndpoints(WebServer &server);

// Handlers de endpoints
void handleAddTag();
void handleListTags();
void handleScanTag();
void handleRemoveTag(); // ← AGREGAR ESTA LÍNEA QUE FALTABA