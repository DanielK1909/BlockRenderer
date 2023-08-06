#include "Log.h"
#include <cstdio>
#include <ctime>

#define _CRT_SECURE_NO_WARNINGS

void Log::sendConsoleMessage(const char* prefix, const char* message) {
	time_t t = time(0);
	std::tm now;
	localtime_s(&now, &t);

	printf("\n%i:%i:%i [%s] %s", now.tm_hour, now.tm_min, now.tm_sec, prefix, message);
}

void Log::error(const char* message) {
	sendConsoleMessage("ERROR", message);
}

void Log::warn(const char* message) {
	sendConsoleMessage("WARN", message);
}

void Log::info(const char* message) {
	sendConsoleMessage("INFO", message);
}
