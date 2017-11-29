#define ERROR_MEMORY_WRITE "Failed writing to memory"
#define ERROR_MEMORY_READ "Unable to read from memory"
#define ERROR_PROCESS "Unable to open process"
#define ERROR_MODULE "Failed opening module"
#define ERROR_NOT_OPEN "Please make sure Dungeons of Dredmor is open"

#define BASEADDR 0x00606C64
#define OFFSET_GOLD 0x620

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <TlHelp32.h>

const char *winStr = "Dungeons of Dredmor";
const char *exeStr = "Dungeons of Dredmor.exe";

void exit_with_error(char *err, HANDLE *hProcess);