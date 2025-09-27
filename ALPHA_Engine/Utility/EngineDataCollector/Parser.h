#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <filesystem>

class Parser {
public:
	// Find all .h/.hpp files in given directories
	static std::vector<std::filesystem::path> FindHeaderFiles(const std::vector<std::filesystem::path>& dirs);

	// Read entire file into a string
	static std::string ReadFileToString(const std::filesystem::path& file);

	// Remove comments and normalize spaces (optional, improves regex matching)
	static std::string PreprocessCode(const std::string& code);

	// Check if a class name should be excluded (non-component base classes)
	static bool ShouldExcludeClass(const std::string& parentName);

	// Parse code string and find classes/structs inheriting from known base classes
	static std::unordered_set<std::string> ParseCode(const std::string& code, const std::unordered_set<std::string>& baseClasses);

	// Parse all headers
	static std::unordered_set<std::string> ParseHeaders(const std::vector<std::filesystem::path>& headers, const std::unordered_set<std::string>& baseClasses);
};