#pragma once

struct Log {

	static void sendConsoleMessage(const char* prefix, const char* message);

	static void error(const char* message);
	static void warn(const char* message);
	static void info(const char* message);

};