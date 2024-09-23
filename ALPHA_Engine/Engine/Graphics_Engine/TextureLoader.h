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

	Texture* _texture;
	std::string _path;

public:
	TextureWork(Texture& texture, std::string path);

private:
	TextureWork();
	void CompleteTask();

public:
	friend ThreadObject;
	friend TextureLoader;
};

class ThreadObject {
private:
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
	~TextureLoader();

	static void Init();

	static void AddTask(Texture& texture, std::string _path);
	static void AddTask(TextureWork work);
	//static void AddTask();
	static void DoWork();

	friend ThreadObject;
};