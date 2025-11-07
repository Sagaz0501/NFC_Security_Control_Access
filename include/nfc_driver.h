#pragma once
#include <Arduino.h>

// Estructura de los usuarios NFC autorizados.

struct NFCtag{
    String uid;
    String name;
    bool authorized;
};

// funciones principales

void setupNFC();
void checkNFCTags();

//Funciones de lectura
bool isTagAuthorized(String uid);
void loadAuthorizedTags();
void saveAuthorizedTag();
void addAuthorizedTag(String uid, String name, bool authorized);
void removeAuthorizedTag(String uid);