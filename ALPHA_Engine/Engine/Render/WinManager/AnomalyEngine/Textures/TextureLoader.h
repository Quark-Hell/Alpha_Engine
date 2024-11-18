#pragma once
#include <list>
#include <memory>
#include <string>
#include <thread>

namespace Render::WindowsManager::AnomalyEngine {

    class TextureWork;
    class ThreadObject;
    class TextureLoader;

    class BaseTexture;

    class TextureWork {
        friend ThreadObject;
        friend TextureLoader;

    private:
        BaseTexture* _texture;
        const std::string _path;
        ThreadObject* _parent = nullptr;

    private:
        TextureWork() = delete;
        void CompleteTask() const;

    public:
        TextureWork(BaseTexture& texture, const std::string& path);
    };

    class ThreadObject {
        friend TextureLoader;
        friend TextureWork;

    private:
        std::thread _thread = std::thread();
        bool _isActive = false;

    private:
        ThreadObject() = default;
        void Start(const std::shared_ptr<TextureWork> &work);

    public:
        ~ThreadObject() = default;
    };


    class TextureLoader {
        friend ThreadObject;

    private:
        std::list<std::shared_ptr<TextureWork>> _taskList;
        std::list<std::unique_ptr<ThreadObject>> _threads;
        const uint8_t _threadsCount;
        static constexpr uint8_t _maxThreadCount = 4;

    public:
        static TextureLoader* GetInstance();

        TextureLoader(const TextureLoader&) = delete;
        TextureLoader& operator=(const TextureLoader&) = delete;
        TextureLoader(TextureLoader&&) = delete;
        TextureLoader& operator=(TextureLoader&&) = delete;

        ~TextureLoader();

        void AddTask(BaseTexture &texture, const std::string &path);
        void DoWork();

    private:
        TextureLoader();
    };
}
