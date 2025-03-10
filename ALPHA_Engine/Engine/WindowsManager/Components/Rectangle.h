#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>
#include "Core/Math/Vectors.h"

namespace WindowsManager {
    class Window;

    class Rectangle {
        friend class Window;

    private:
        //Left bottom corner
        glm::vec2 _position{0,0};
        //For calculate right bottom corner just add _size to _position
        glm::vec2 _size{1,1};

        glm::vec2 _maxSize{1,1};
        glm::vec2 _minSize{0.05,0.05};

        std::vector<Rectangle*> _topNeighbors{};
        std::vector<Rectangle*> _bottomNeighbors{};

        std::vector<Rectangle*> _leftNeighbors{};
        std::vector<Rectangle*> _rightNeighbors{};

        Rectangle(const glm::vec2& position, const glm::vec2& size);

    public:
        void SetPosition(const glm::vec2& position);

        void SetSize(const glm::vec2& size);
        void SetMaxSize(const glm::vec2& maxSize);
        void SetMinSize(const glm::vec2& minSize);

    public:
        [[nodiscard]] glm::vec2 GetPosition() const;
        [[nodiscard]] glm::vec2 GetSize() const;

        [[nodiscard]] glm::vec2 GetMaxSize() const;
        [[nodiscard]] glm::vec2 GetMinSize() const;

        [[nodiscard]] glm::vec2 GetLeftTopCorner() const;
        [[nodiscard]] glm::vec2 GetLeftBottomCorner() const;

        [[nodiscard]] glm::vec2 GetRightTopCorner() const;
        [[nodiscard]] glm::vec2 GetRightBottomCorner() const;

    public:
        Rectangle() = delete;
        ~Rectangle() = default;
    };
}

#endif //RECTANGLE_H
