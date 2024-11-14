#include "TextureLoader.h"

#include <iostream>
#include "BaseTexture.h"

namespace Render::AnomalyEngine::Textures {

    TextureWork::TextureWork(BaseTexture& texture, const std::string& path) : _texture(&texture), _path(path) {}

    void TextureWork::CompleteTask() const {
        if (_parent != nullptr) {
            _texture->CreateTexture(_path);
            std::cout << "Info: Work completed" << std::endl;
            _parent->_isActive = false;
        }
        else {
            std::cout << "Error: parent is null" << std::endl;
        }
    }

    //-------------------------------------------------------------------------//


    void ThreadObject::Start(const std::shared_ptr<TextureWork> &work)
    {
        if (work.get() == nullptr) {
            std::cout << "Error: Work is null" << std::endl;
            return;
        }

        if (_thread.joinable()) {
            _thread.join();
        }

        work->_parent = this;
        _isActive = true;
        _thread = std::thread(&TextureWork::CompleteTask, work);
        std::cout << "Info: thread activated" << std::endl;
    }

    //-------------------------------------------------------------------------//

    TextureLoader::TextureLoader() : _threadsCount(std::min(static_cast<uint8_t>(std::thread::hardware_concurrency()), _maxThreadCount)) {}

    TextureLoader* TextureLoader::GetInstance() {
        static TextureLoader instance;
        return &instance;
    }

    TextureLoader::~TextureLoader()
    {
        for (const auto& it : _threads) {
            if (it->_thread.joinable()) {
                it->_thread.join();
            }
        }
    }

    void TextureLoader::AddTask(BaseTexture &texture, const std::string &path)
    {
        _taskList.emplace_back(std::make_shared<TextureWork>(texture, path));
    }

    void TextureLoader::DoWork()
    {
        if (_taskList.empty()) {
            std::cout << "Error: no task" << std::endl;
            return;
        }

        for (unsigned int i = 0; i < _threadsCount; i++) {
            _threads.emplace_back(std::unique_ptr<ThreadObject>(new ThreadObject));
        }

        while (_taskList.size() > 0) {
            for (const auto& it : _threads) {
                if (it->_isActive == false) {

                    it->Start(_taskList.back());
                    _taskList.pop_back();

                    if (_taskList.size() == 0) {
                        break;
                    }
                }
            }
        }

        //Waits until all threads finish working
        for (const auto& it : _threads) {
            if (it->_thread.joinable()) {
                it->_thread.join();
            }
        }

        _threads.clear();
    }

}