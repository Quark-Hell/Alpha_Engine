#include "Rectangle.h"
#include "Core/Logger/Logger.h"

namespace WindowsManager {
    Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& size) :
    _position(position), _size(size) {}

    glm::vec2 Rectangle::GetPosition() const { return _position; }

    glm::vec2 Rectangle::GetSize() const { return _size; }
    glm::vec2 Rectangle::GetMaxSize() const { return _maxSize; }
    glm::vec2 Rectangle::GetMinSize() const { return _minSize; }

    glm::vec2 Rectangle::GetLeftTopCorner() const {
        glm::vec2 corner = _position;
        corner.y += _size.y;

        return corner;
    }
    glm::vec2 Rectangle::GetLeftBottomCorner() const {
        glm::vec2 corner = _position;

        return corner;
    }
    glm::vec2 Rectangle::GetRightTopCorner() const {
        glm::vec2 corner = _position + _size;

        return corner;
    }
    glm::vec2 Rectangle::GetRightBottomCorner() const {
        glm::vec2 corner = _position;
        corner.x += _size.x;

        return corner;
    }

    void Rectangle::SetPosition(const glm::vec2& position) {
        if(position.x < 0 || position.y < 0){
            Core::Logger::LogError("Position should be positive: " + __LOGERROR__);
            return;
        }

        if (position.x > 1 || position.y > 1) {
            Core::Logger::LogWarning("Position should be normalized");
            _position = glm::normalize(position);
            return;
        }

        _position = position;
    }
    void Rectangle::SetSize(const glm::vec2& size) {
        if(size.x < 0 || size.y < 0){
            Core::Logger::LogError("Size should be positive: " + __LOGERROR__);
            return;
        }

        if (size.x > 1 || size.y > 1) {
            Core::Logger::LogWarning("Size should be normalized.");
            _size = glm::normalize(size);
            return;
        }

        _size = size;
    }

    void Rectangle::SetMaxSize(const glm::vec2& maxSize) {
        if(maxSize.x < 0 || maxSize.y < 0){
            Core::Logger::LogError("Maximum size should be positive: " + __LOGERROR__);
            return;
        }

        if (maxSize.x > 1 || maxSize.y > 1) {
            Core::Logger::LogWarning("Maximum size should be normalized.");
            _size = glm::normalize(maxSize);
            return;
        }

        _maxSize = maxSize;
    }
    void Rectangle::SetMinSize(const glm::vec2& minSize) {
        if(minSize.x < 0 || minSize.y < 0){
            Core::Logger::LogError("Minimal size should be positive: " + __LOGERROR__);
            return;
        }

        if (minSize.x > 1 || minSize.y > 1) {
            Core::Logger::LogWarning("Minimal size should be normalized.");
            _minSize = glm::normalize(minSize);
            return;
        }

        _minSize = minSize;
    }
}