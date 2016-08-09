#pragma once
#ifdef WIN32
#define RM_PATH "../Resources/Data/RM.json"
#define FM_PATH "../Resources/Data/FM.json"
#define AM_PATH "../Resources/Data/AM.json"
#define FONT_PATH "../Resources/Fonts/arial.ttf"
#define DATA_PATH "../Resources/"

#else
#define RM_PATH "/sdcard/Resources/Data/RM.json"
#define FM_PATH "/sdcard/Resources/Data/FM.json"
#define AM_PATH "/sdcard/Resources/Data/AM.json"
#define FONT_PATH "/sdcard/Resources/Fonts/arial.ttf"
#define DATA_PATH "/sdcard/Resources/"

#endif
