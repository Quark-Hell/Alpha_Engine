#pragma once
#include "BaseConfig.h"

class Tag
{
private:
	static inline std::map<std::string, unsigned> _availableTags = {
		{"Object", 0},
		{"Player", 1},
		{"SkyBox", 2}
	};
	std::string _tag;

public:
	Tag();
	~Tag();

	bool SetTag(std::string tag);
	bool SetTag(unsigned int tagIndex);
	std::string GetTag();
	std::vector<std::string> GetAvailablesTag();
};

