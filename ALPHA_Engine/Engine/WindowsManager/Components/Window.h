#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>

#include "Rectangle.h"
#include "Core/Math/glmMath.h"

struct GLFWwindow;
struct GLFWmonitor;

namespace WindowsManager {

    class Window {
        friend class WindowsManager;
        friend class WindowsBuffer;

        enum Direction {
            NotAvailable = 0,
            Left         = 1,
            Right        = 2,
            Top          = 3,
            Bottom       = 4
        };

        class Buffer {
        public:
            Rectangle* Rect = nullptr;
            float OriginDelta = 0;
            float FoundDelta = 0;
            Direction Direct = Direction::NotAvailable;

            Buffer() = delete;
            Buffer(Rectangle* rect, float origin, float found, Direction direct) {
                Rect = rect;
                OriginDelta = origin;
                FoundDelta = found;
                Direct = direct;
            }
        };

    private:
        GLFWwindow *_window;

        glm::vec2 _size = glm::vec2(600, 480);

        std::string _title = "Window";

        std::vector<std::unique_ptr<Rectangle>> _rectangles;

        bool _isSync = true;
        bool _isCursorVisible = true;

        const float _algEpsilon = 0.000005f;

    private:
        void SetWindowHints();
        Window(const glm::vec2& size, const std::string& title, GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr);

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

    private:
        void PushLeftRectEdge(
                float delta,
                Rectangle& support,
                const std::shared_ptr<std::vector<Buffer>>& checkedPos,
                const std::shared_ptr<std::vector<Buffer>>& checkedSize,
                Rectangle* origin,
                bool isHeader = false);

        void PushRightRectEdge(
                float delta,
                Rectangle& support,
                const std::shared_ptr<std::vector<Buffer>>& checkedPos,
                const std::shared_ptr<std::vector<Buffer>>& checkedSize,
                Rectangle* origin,
                bool isHeader = false);


        void PushRectToLeft (
                float delta,
                Rectangle& support,
                const std::shared_ptr<std::vector<Buffer>>& checkedPos,
                const std::shared_ptr<std::vector<Buffer>>& checkedSize,
                Rectangle* origin,
                bool isHeader = false);

        void PushRectToRight (
                float delta,
                Rectangle& support,
                const std::shared_ptr<std::vector<Buffer>>& checkedPos,
                const std::shared_ptr<std::vector<Buffer>>& checkedSize,
                Rectangle* origin,
                bool isHeader = false
        );

        void PushTopRectEdge(
                float delta,
                Rectangle& support,
                const std::shared_ptr<std::vector<Buffer>>& checkedPos,
                const std::shared_ptr<std::vector<Buffer>>& checkedSize,
                Rectangle* origin,
                bool isHeader = false);

        void PushBottomRectEdge(
                float delta,
                Rectangle& support,
                const std::shared_ptr<std::vector<Buffer>>& checkedPos,
                const std::shared_ptr<std::vector<Buffer>>& checkedSize,
                Rectangle* origin,
                bool isHeader = false);

        void PushRectToUp (
                float delta,
                Rectangle& support,
                const std::shared_ptr<std::vector<Buffer>>& checkedPos,
                const std::shared_ptr<std::vector<Buffer>>& checkedSize,
                Rectangle* origin,
                bool isHeader = false);

        void PushRectToDown (
                float delta,
                Rectangle& support,
                const std::shared_ptr<std::vector<Buffer>>& checkedPos,
                const std::shared_ptr<std::vector<Buffer>>& checkedSize,
                Rectangle* origin,
                bool isHeader = false
        );

        void ApplyChangesX(
                float delta,
                const std::shared_ptr<std::vector<Buffer>>& checkedPos,
                const std::shared_ptr<std::vector<Buffer>>& checkedSize);

        void ApplyChangesY(
                float delta,
                const std::shared_ptr<std::vector<Buffer>> &checkedPos,
                const std::shared_ptr<std::vector<Buffer>>& checkedSize);

        void LeftEnd(Rectangle& support);
        void RightEnd(Rectangle& support);

        void TopEnd(Rectangle& support);
        void BottomEnd(Rectangle& support);

        bool HasPathLeft(Rectangle& rect, Rectangle& origin);
        bool HasPathRight(Rectangle& rect, Rectangle& origin);

        bool HasPathTop(Rectangle& rect, Rectangle& origin);
        bool HasPathBottom(Rectangle& rect, Rectangle& origin);

    public:
        void PushLeftRectEdge(float delta, Rectangle& support);
        void PushRightRectEdge(float delta, Rectangle& support);
        void PushTopRectEdge(float delta, Rectangle& support);
        void PushBottomRectEdge(float delta, Rectangle& support);

        void PushRectToLeft(float delta, Rectangle& support);
        void PushRectToRight(float delta, Rectangle& support);


        void RectangleFillFreeSpace(Rectangle& support);

        [[nodiscard]] glm::vec2 GetRectangleSize(size_t index) const;
        [[nodiscard]] glm::vec2 GetRectanglePosition(size_t index) const;

        [[nodiscard]] bool CheckRectangleExist(size_t index) const;

//=============================RECTANGLE SETTINGS=============================//
    };
}
