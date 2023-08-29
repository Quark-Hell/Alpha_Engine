#pragma once
#include "Basical_Type.h"

enum ImportPriotity : uint8_t {
	Low = 0,
	Medium = 1,
	High = 2,
	Max = 3
};

class ImportProcess {
private:
	ImportPriotity _priority;

public:
	ImportProcess();
	~ImportProcess();

	ImportPriotity GetProcessPriority();

	void SetPriority(ImportPriotity newPriority);
};

static class SceneImporter
{
private:
	std::queue<ImportProcess> _asyncProcessBuffer;

public:
	SceneImporter();
	~SceneImporter();

	void ForceImportFolder(std::string pathToFolder);
	void AsyncImportFolder(ImportPriotity priority, std::string pathToFolder);

};

