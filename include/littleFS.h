#pragma once

#include <Arduino.h>
#include <LittleFS.h>
#include "FS.h"

#define FORAMT_LITTLEFS_IF_FAILED true

void createDir(fs::FS &fs, const char * path);
void readFile(fs::FS &fs, const char * path);
void writeFile(fs::FS &fs, const char * path, const char * message);
void appendFile(fs::FS &fs, const char * path, const char * message);
void testFileIO(fs::FS &fs, const char * path);

void setupLittleFS();