#pragma once

#include "ILogger.h"

class ConsoleLogger : ILogger {
public:
	int ColorMessage;
	int ColorWarning;
	int ColorError;

	ConsoleLogger();
	~ConsoleLogger();

	void WriteMessage(const char& text) override;
	void WriteWarning(const char& text) override;
	void WriteError(const char& text) override;
};