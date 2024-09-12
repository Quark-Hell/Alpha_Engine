#pragma once
#include "iostream"

class ILogger {
	virtual void WriteMessage(const char& text) = 0;
	virtual void WriteWarning(const char& text) = 0;
	virtual void WriteError(const char& text) = 0;

	virtual ~ILogger() {};
};