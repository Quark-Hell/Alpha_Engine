#pragma once
#include "Texture.h"
#include <mutex>

class TextureWork;
class ThreadObject;
class TextureLoader;

class TextureWork {
private:
	ThreadObject* parent = nullptr;
	bool _tryStopThread = false;

public:
	Texture* _texture;

	std::string _path;
	bool _genTextureAuto = true;
	bool _unbindTextureAuto = true;
	EnumTypeOfTexture _typeOfTexture = EnumTypeOfTexture::Texture2D;

private:
	void CompleteTask();

public:
	friend ThreadObject;
	friend TextureLoader;
};

class ThreadObject {
private:
	//std::thread* _thread = new std::thread(&TextureWork::CompleteTask, &_work);
	std::thread _thread = std::thread();

	TextureWork _work;
	bool _isActive = false;
	bool _isStarted = false;
	bool _isAlive = true;

	bool tryDeleteThread = false;
	void DeleteThread();

public:
	ThreadObject();
	~ThreadObject();

	void Start(TextureWork work);
	void Continue(TextureWork work);

	friend TextureLoader;
	friend TextureWork;
};

class TextureLoader {
private:
	static inline std::list<TextureWork> _taskList;
	static inline std::vector<std::unique_ptr<ThreadObject>> _threads;

public:
	static inline unsigned int MaxThreadCount = 4;

public:
	TextureLoader();
	~TextureLoader();

	static void Init();

	static void AddTask(Texture* texture, std::string _path, bool _genTextureAuto = true, bool _unbindTextureAuto = true, EnumTypeOfTexture _typeOfTexture = EnumTypeOfTexture::Texture2D);
	static void AddTask(TextureWork work);
	static void AddTask();
	static void DoWork();

private:
	//Logic inverted. Is get 0 then one or more threads is active now

	friend ThreadObject;
};