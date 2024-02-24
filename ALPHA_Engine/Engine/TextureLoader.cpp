#include "TextureLoader.h"

TextureLoader::TextureLoader()
{

}

TextureLoader::~TextureLoader()
{
}

void TextureLoader::Init()
{
	unsigned int n = std::min(std::thread::hardware_concurrency(), MaxThreadCount);

	for (unsigned int i = 0; i < n; i++) {
		std::unique_ptr<ThreadObject> obj = std::make_unique<ThreadObject>();
		_threads.push_back(std::move(obj));
	};
}

void TextureLoader::AddTask(Texture* texture, std::string _path, bool _genTextureAuto, bool _unbindTextureAuto, EnumTypeOfTexture _typeOfTexture)
{
	TextureWork newTask;
	newTask._texture = texture;
	newTask._path = _path;
	newTask._genTextureAuto = _genTextureAuto;
	newTask._unbindTextureAuto = _unbindTextureAuto;
	newTask._typeOfTexture = _typeOfTexture;
	
	TextureLoader::_taskList.push_back(newTask);
}

void TextureLoader::AddTask(TextureWork work)
{
	TextureLoader::_taskList.push_back(work);
}

void TextureLoader::AddTask()
{
	TextureWork newTask;
	TextureLoader::_taskList.push_back(newTask);
}

void TextureLoader::DoWork()
{
	TextureLoader::Init();
	
	while (TextureLoader::_taskList.size() != 0 && TextureLoader::_threads.size() != 0) {
			for (size_t i = 0; i < TextureLoader::_threads.size(); i++) {
				if (TextureLoader::_threads[i]->_isStarted == false) {
					//std::cout << TextureLoader::_taskList.begin()._Ptr << "\n";
					TextureLoader::_threads[i]->Start(TextureLoader::_taskList.begin()._Ptr->_Myval);

					TextureLoader::_taskList.erase(TextureLoader::_taskList.begin());
					break;
				}
	
				if (TextureLoader::_threads[i]->_isActive == true)
					continue;
	
				TextureLoader::_threads[i]->Continue(TextureLoader::_taskList.begin()._Ptr->_Myval);
				TextureLoader::_taskList.erase(TextureLoader::_taskList.begin());
				break;
			}
	}
	
	TextureLoader::_threads.clear();
}

void ThreadObject::DeleteThread() {
	_isAlive = false;
}

void TextureWork::CompleteTask()
{
	using namespace std::chrono_literals;

	while (parent->_isAlive)
	{
		if (parent->tryDeleteThread) {
			parent->DeleteThread();
		}

		if (parent->_isActive == true) {
			std::cout << "I work\n";
			parent->_isActive = false;
		}
	}
}

ThreadObject::ThreadObject()
{
}

ThreadObject::~ThreadObject()
{
	if (_isStarted) {
		ThreadObject::tryDeleteThread = true;
		ThreadObject::_thread.join();
	}
}


void ThreadObject::Start(TextureWork work)
{
	ThreadObject::_work = work;
	ThreadObject::_work.parent = this;
	ThreadObject::_work.parent->_isActive = true;
	ThreadObject::_thread = std::thread(&TextureWork::CompleteTask, &_work);
	ThreadObject::_isStarted = true;
}

void ThreadObject::Continue(TextureWork work)
{
	work.parent = this;
	ThreadObject::_work = work;
	ThreadObject::_work.parent->_isActive = true;
}