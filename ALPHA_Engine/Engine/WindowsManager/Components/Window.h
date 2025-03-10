#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>

#include "Rectangle.h"
#include "Core/Math/Vectors.h"
#include "Core/Math/glmMath.h"

struct GLFWwindow;
struct GLFWmonitor;

namespace WindowsManager {

    class Window {
        friend class WindowsManager;
        friend class WindowsBuffer;

    private:
        GLFWwindow *_window;

        glm::vec2 _size = glm::vec2(600, 480);

        std::string _title = "Window";

        std::vector<std::unique_ptr<Rectangle>> _rectangles;
        std::vector<std::pair<glm::vec2, glm::vec2>> _freeRectangles {
            {{0,0}, {1,1}}
        };

        bool _isSync = true;
        bool _isCursorVisible = true;

    private:
        void SetWindowHints();
        Window(const glm::vec2& size, const std::string& title, GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr);

        void RecalculateFreeSpace(const Rectangle& support);

        void ResizeRectangle(Rectangle& support, glm::vec2 newSize);

        void RecalculateRectangleNeighbors(Rectangle& support);

    public:

        Window() = delete;
        ~Window();

//=============================WINDOW SETTINGS=============================//

        void Resize(const glm::vec2& size);

        void SetSync(bool sync);
        void SetCursorVisible(bool isVisible);
        void SetTitle(const std::string& title);
        void SetSize(const glm::vec2& size);
        void SetPosition(const glm::vec2& position);

        [[nodiscard]] bool GetCursorVisible() const;
        [[nodiscard]] std::string GetTitle();
        [[nodiscard]] glm::vec2 GetSize();
        [[nodiscard]] GLFWwindow *GetGLFWwindow() const;

//=============================WINDOW SETTINGS=============================//

//=============================RECTANGLE SETTINGS=============================//

        Rectangle& CreateRectangle(
            const glm::vec2& position = glm::vec2(0.0f, 0.0f),
            const glm::vec2& size = glm::vec2(1.0f, 1.0f));

        [[nodiscard]] Rectangle& GetRectangle(size_t index);

        //TODO: Make it
        void DestroyRectangle(size_t index);

        //X component - change left edge
        //Y component - change right edge
        float PushLeftRectEdge(
                float delta,
                Rectangle& support,
                std::shared_ptr<std::vector<std::pair<Rectangle*, bool>>> checked);

        float PushRightRectEdge(
                float delta,
                Rectangle& support,
                std::shared_ptr<std::vector<std::pair<Rectangle*, bool>>> checked);


        float PushLeftRect (
                float delta,
                Rectangle& support,
                std::shared_ptr<std::vector<std::pair<Rectangle*, bool>>> checked
                );

        void SetRectanglePosition(const glm::vec2& position, size_t index);

        void RectangleFillFreeSpace(Rectangle& support);

        [[nodiscard]] glm::vec2 GetRectangleSize(size_t index) const;
        [[nodiscard]] glm::vec2 GetRectanglePosition(size_t index) const;

        [[nodiscard]] bool CheckRectangleExist(size_t index) const;

//=============================RECTANGLE SETTINGS=============================//
    };
}
