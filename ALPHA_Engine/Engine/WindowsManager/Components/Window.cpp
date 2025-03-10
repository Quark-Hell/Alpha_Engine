#include "Window.h"

#include <limits>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Core/Logger/Logger.h"

void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::cout << "---------------------opengl-callback-start------------" << std::endl;
    std::cout << "message: "<< message << std::endl;
    std::cout << "type: ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            std::cout << "ERROR";
        break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "DEPRECATED_BEHAVIOR";
        break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "UNDEFINED_BEHAVIOR";
        break;
        case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "PORTABILITY";
        break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "PERFORMANCE";
        break;
        case GL_DEBUG_TYPE_OTHER:
            std::cout << "OTHER";
        break;
    }
    std::cout << std::endl;

    std::cout << "id: " << id << std::endl;
    std::cout << "severity: ";
    switch (severity){
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "LOW";
        break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "MEDIUM";
        break;
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "HIGH";
        break;
    }
    std::cout << std::endl;
    std::cout << "---------------------opengl-callback-end--------------" << std::endl;
}


namespace WindowsManager {
    Window::~Window() {
        glfwDestroyWindow(_window);
    }

    void Window::SetWindowHints() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        glfwWindowHint(GLFW_SAMPLES, 4);
    }

    Window::Window(const glm::vec2& size, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share) {
        SetWindowHints();

        SetSize(size);
        SetTitle(title);

        const int width = static_cast<int>(_size.x);
        const int height = static_cast<int>(_size.y);
        _window = glfwCreateWindow(width, height, title.c_str(), monitor, share);

        if (_window == nullptr)
        {
            Core::Logger::LogCritical("Failed to create GLFW window: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            glfwTerminate();
            abort();
        }

        glfwMakeContextCurrent(_window);
        glfwSwapInterval(1);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            glfwTerminate();
            Core::Logger::LogCritical("Critical: glad does not inited: " + std::string(__FILE__ ":") + std::to_string(__LINE__));
        }

        glEnable(GL_MULTISAMPLE);

        int bufferWidth, bufferHeight;
        glfwGetFramebufferSize(_window, &bufferWidth, &bufferHeight);
        if (_size.x > _size.y) {
            glViewport(0, static_cast<int>(_size.y - _size.x) / 2, bufferWidth, bufferHeight);
        }
        else {
            glViewport(static_cast<int>(_size.x - _size.y) / 2, 0, bufferWidth, bufferHeight);
        }

        glEnable(GL_DEBUG_OUTPUT );
        glDebugMessageCallback(openglCallbackFunction, 0);
    }

    void Window::SetSync(const bool sync) {
        _isSync = sync;

        glfwMakeContextCurrent(_window);
        if (_isSync) glfwSwapInterval(1);
        else glfwSwapInterval(0);
    }

    bool Window::GetCursorVisible() const {
        return _isCursorVisible;
    }

    void Window::SetCursorVisible(const bool isVisible) {
        _isCursorVisible = isVisible;

        if (_isCursorVisible)
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        else
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void Window::SetTitle(const std::string& title) {
        _title = title;
    }

    std::string Window::GetTitle() {
        return _title;
    }


    glm::vec2 Window::GetSize() {
        return _size;
    }

    void Window::SetSize(const glm::vec2& size) {
        if (size.x < 0) {
            Core::Logger::LogError("X size should be positive: " + __LOGERROR__);
            return;
        }
        if (size.y < 0) {
            Core::Logger::LogError("Y size should be positive: " + __LOGERROR__);
            return;
        }

        _size = size;
    }

    GLFWwindow *Window::GetGLFWwindow() const {
        return _window;
    }

    void Window::RecalculateRectangleNeighbors(Rectangle& support) {
        std::pair<glm::vec2, glm::vec2> topEdge      {support.GetLeftTopCorner(),     support.GetRightTopCorner() };
        std::pair<glm::vec2, glm::vec2> bottomEdge   {support.GetLeftBottomCorner(),  support.GetRightBottomCorner() };

        std::pair<glm::vec2, glm::vec2> leftEdge     {support.GetLeftBottomCorner(),  support.GetLeftTopCorner() };
        std::pair<glm::vec2, glm::vec2> rightEdge    {support.GetRightBottomCorner(), support.GetRightTopCorner() };

#pragma region Functions
        auto findDistance = [](
                const glm::vec2 norm,
                const glm::vec2& corner1,
                const glm::vec2& corner2,
                const glm::vec2& itP1,
                const glm::vec2& itP2,
                size_t index,
                std::vector<std::pair<size_t, float>>& distances) {

                glm::vec2 p1 = glm::ProjectPointOnAxis(corner1, itP1, itP2);
                glm::vec2 p2 = glm::ProjectPointOnAxis(corner2, itP1, itP2);

                glm::vec2 vec = p1 - corner1;

                constexpr float epsilon = 0.01f;

                if (std::fabs(glm::dot(vec, norm)) > epsilon) {
                    if (glm::dot(glm::normalize(vec), norm) < 0)
                        return;
                }


                bool exp1 = glm::InSegment(p1, itP1, itP2);
                bool exp2 = glm::InSegment(p2, itP1, itP2);

                bool exp3 = glm::InSegment(itP1, p1, p2);
                bool exp4 = glm::InSegment(itP2, p1, p2);


                if((exp1 + exp2 + exp3 + exp4) < 2)
                    return;

                distances.emplace_back(index, glm::length2(vec));
        };

        constexpr float epsilon = 0.001f;
        auto removeExtra = [](std::vector<std::pair<size_t, float>>& distances, float eps) {
            distances.erase(
                    std::remove_if(distances.begin(), distances.end(),
                                   [&](const auto& pair) { return pair.second > eps; }),
                    distances.end()
            );
        };

#define REMOVE_DEPENDENCIES(support, supportVector, neighborVector) \
    for (size_t it = 0; it < support.supportVector.size(); it++) { \
        for (size_t jt = 0; jt < support.supportVector[it]->neighborVector.size(); jt++) { \
            if (&support == support.supportVector[it]->neighborVector[jt]) { \
                size_t size = support.supportVector[it]->neighborVector.size(); \
                std::swap( \
                        support.supportVector[it]->neighborVector[jt], \
                        support.supportVector[it]->neighborVector[size - 1]); \
                support.supportVector[it]->neighborVector.pop_back(); \
            } \
        } \
    }

#define ADD_DEPENDENCIES(supportVector, neighborVector) \
    for (size_t it = 0; it < support.supportVector.size(); it++) { \
        support.supportVector[it]->neighborVector.emplace_back(&support); \
    }

#pragma endregion

        //We don't need to calculate neighbors tree if support the only one rectangle
        if (_rectangles.empty() || _rectangles.size() == 1) {
            support._topNeighbors.clear();
            support._bottomNeighbors.clear();
            support._leftNeighbors.clear();
            support._rightNeighbors.clear();

            return;
        }

        //first  - index in rectangle vector
        //second - distance
        std::vector<std::pair<size_t, float>> bufferDistances;
        bufferDistances.reserve(_rectangles.size() - 1);

        REMOVE_DEPENDENCIES(support, _topNeighbors, _bottomNeighbors);
        REMOVE_DEPENDENCIES(support, _bottomNeighbors, _topNeighbors);
        REMOVE_DEPENDENCIES(support, _leftNeighbors, _rightNeighbors);
        REMOVE_DEPENDENCIES(support, _rightNeighbors, _leftNeighbors);

        support._topNeighbors.clear();
        support._bottomNeighbors.clear();
        support._leftNeighbors.clear();
        support._rightNeighbors.clear();

#pragma region Emplace Neighbors

        glm::vec2 topNorm    {0,  1};
        glm::vec2 bottomNorm {0, -1};

        glm::vec2 leftNorm   {-1, 0};
        glm::vec2 rightNorm  {1,  0};


#pragma region find top neighbors
        for (size_t i = 0; i < _rectangles.size(); i++) {
            auto& it = _rectangles[i];
            if (it.get() == &support) continue;

            findDistance(
                    topNorm,
                    support.GetLeftTopCorner(),
                    support.GetRightTopCorner(),
                    it->GetLeftBottomCorner(),
                    it->GetRightBottomCorner(),
                    i,
                    bufferDistances);
        }
        removeExtra(bufferDistances, epsilon);

        for (auto & bf : bufferDistances) {
            support._topNeighbors.emplace_back(_rectangles[bf.first].get());
        }
        bufferDistances.clear();
#pragma endregion

#pragma region find bottom neighbors
        for (size_t i = 0; i < _rectangles.size(); i++) {
            auto& it = _rectangles[i];
            if (it.get() == &support) continue;

            findDistance(
                    bottomNorm,
                    support.GetLeftBottomCorner(),
                    support.GetRightBottomCorner(),
                    it->GetLeftTopCorner(),
                    it->GetRightTopCorner(),
                    i,
                    bufferDistances);
        }
        removeExtra(bufferDistances, epsilon);

        for (auto & bf : bufferDistances) {
            support._bottomNeighbors.emplace_back(_rectangles[bf.first].get());
        }
        bufferDistances.clear();
#pragma endregion

#pragma region find left neighbors
        for (size_t i = 0; i < _rectangles.size(); i++) {
            auto& it = _rectangles[i];
            if (it.get() == &support) continue;

            findDistance(
                    leftNorm,
                    support.GetLeftBottomCorner(),
                    support.GetLeftTopCorner(),
                    it->GetRightBottomCorner(),
                    it->GetRightTopCorner(),
                    i,
                    bufferDistances);
        }
        removeExtra(bufferDistances, epsilon);

        for (auto & bf : bufferDistances) {
            support._leftNeighbors.emplace_back(_rectangles[bf.first].get());
        }
        bufferDistances.clear();
#pragma endregion

#pragma region find right neighbors
        for (size_t i = 0; i < _rectangles.size(); i++) {
            auto& it = _rectangles[i];
            if (it.get() == &support) continue;

            findDistance(
                    rightNorm,
                    support.GetRightBottomCorner(),
                    support.GetRightTopCorner(),
                    it->GetLeftBottomCorner(),
                    it->GetLeftTopCorner(),
                    i,
                    bufferDistances);
        }
        removeExtra(bufferDistances, epsilon);

        for (auto & bf : bufferDistances) {
            support._rightNeighbors.emplace_back(_rectangles[bf.first].get());
        }
        bufferDistances.clear();
#pragma endregion

#pragma endregion

        ADD_DEPENDENCIES(_topNeighbors, _bottomNeighbors);
        ADD_DEPENDENCIES(_bottomNeighbors, _topNeighbors);
        ADD_DEPENDENCIES(_leftNeighbors, _rightNeighbors);
        ADD_DEPENDENCIES(_rightNeighbors, _leftNeighbors);
    }

    void Window::ResizeRectangle(Rectangle& support, glm::vec2 newSize) {


    }

    void Window::RecalculateFreeSpace(const Rectangle& support) {
        //find intersect AABB
        //It may be more than 1
        //So we need check vector at all
        std::vector<std::pair<glm::vec2, glm::vec2>*> intersectBuffer;
        std::vector<size_t> indexBuffer;

        size_t index = 0;
        for(auto& rect : _freeRectangles) {
            glm::vec2 leftCorner = rect.first;
            glm::vec2 rightCorner = rect.second;

            bool intersect = glm::CheckAABBIntersection(
                    support.GetLeftBottomCorner(),
                    support.GetRightTopCorner(),
                    leftCorner,
                    rightCorner);

            if(intersect) {
                intersectBuffer.emplace_back(&rect);
                indexBuffer.emplace_back(index);
            }

            index++;
        }

        //Divide intersect rectangle
        for(size_t i = intersectBuffer.size(); i--;){
            std::vector<std::pair<glm::vec2, glm::vec2>> pushBuffer;
            pushBuffer.resize(4);

            //Calculate left rectangle
            pushBuffer[0].first    = intersectBuffer[i]->first;
            pushBuffer[0].second.x = support.GetLeftBottomCorner().x;
            pushBuffer[0].second.y = intersectBuffer[i]->second.y;

            //Calculate top rectangle
            pushBuffer[1].first.x  = intersectBuffer[i]->first.x;
            pushBuffer[1].first.y  = support.GetRightTopCorner().y;
            pushBuffer[1].second.x = support.GetRightTopCorner().x;
            pushBuffer[1].second.y = intersectBuffer[i]->second.y;

            //Calculate right rectangle
            pushBuffer[2].first.x  = support.GetRightBottomCorner().x;
            pushBuffer[2].first.y  = intersectBuffer[i]->first.y;
            pushBuffer[2].second   = intersectBuffer[i]->second;

            //Calculate bottom rectangle
            pushBuffer[3].first    = intersectBuffer[i]->first;
            pushBuffer[3].second   = support.GetRightBottomCorner();

            //Remove divided rectangle from buffer
            _freeRectangles.erase(_freeRectangles.begin() + indexBuffer[i]);

            //Remove zero rectangle
            for(auto& rect : pushBuffer) {
                //if(rect.first.x == rect.second.x || rect.first.y == rect.second.y) { continue; }
                if(rect.first.x >= rect.second.x) { continue; }
                if(rect.first.y >= rect.second.y) { continue; }

                _freeRectangles.emplace_back(rect);
            }
        }
    }

    void Window::RectangleFillFreeSpace(Rectangle& support) {
        glm::vec2 centerPoint = glm::GetRectangleCenter(
                support.GetLeftBottomCorner(),
                support.GetLeftTopCorner(),
                support.GetRightBottomCorner(),
                support.GetRightTopCorner());

        //Find max upscale distance
        float xLeftMaxDistance = 1, yTopMaxDistance = 1;
        float xRightMaxDistance = 1, yBottomMaxDistance = 1;

        int i = -1;
        for (auto& it : _rectangles) {
            i++;
            if (it.get() == &support) continue;

            //Get nearest edges by X and Y axis

            //find nearest edges
            glm::vec2 rectCenterPoint = glm::GetRectangleCenter(
                    it->GetLeftBottomCorner(),
                    it->GetLeftTopCorner(),
                    it->GetRightBottomCorner(),
                    it->GetRightTopCorner());

            glm::vec2 vec = rectCenterPoint - centerPoint;

            //expression
            bool v1 = false, v2 = false, v3 = false, v4 = false;

            //left
            if (vec.x < 0) {
                glm::vec2 p1 = glm::ProjectPointOnAxis(support.GetLeftBottomCorner(), it->GetRightBottomCorner(), it->GetRightTopCorner());
                glm::vec2 p2 = glm::ProjectPointOnAxis(support.GetLeftTopCorner(), it->GetRightBottomCorner(), it->GetRightTopCorner());

                v1 = glm::InSegment(p1, it->GetRightBottomCorner(), it->GetRightTopCorner());
                v2 = glm::InSegment(p2, it->GetRightBottomCorner(), it->GetRightTopCorner());

                //if (v1 || v2) {
                    glm::vec2 vect = p2 - support.GetLeftTopCorner();
                    float xDist = glm::length(vect);

                    if (xLeftMaxDistance > xDist) xLeftMaxDistance = xDist;
                //}
            }
            //right
            else {
                glm::vec2 p1 = glm::ProjectPointOnAxis(support.GetRightBottomCorner(), it->GetLeftBottomCorner(), it->GetLeftTopCorner());
                glm::vec2 p2 = glm::ProjectPointOnAxis(support.GetRightTopCorner(), it->GetLeftBottomCorner(), it->GetLeftTopCorner());

                v1 = glm::InSegment(p1, it->GetLeftBottomCorner(), it->GetLeftTopCorner());
                v2 = glm::InSegment(p2, it->GetLeftBottomCorner(), it->GetLeftTopCorner());

                //if (v1 || v2) {
                    glm::vec2 vect = p2 - support.GetRightTopCorner();
                    float xDist = glm::length(vect);

                    if (xRightMaxDistance > xDist) xRightMaxDistance = xDist;
                //}
            }

            //bottom
            if (vec.y < 0) {
                glm::vec2 p1 = glm::ProjectPointOnAxis(support.GetLeftBottomCorner(), it->GetLeftTopCorner(), it->GetRightTopCorner());
                glm::vec2 p2 = glm::ProjectPointOnAxis(support.GetRightBottomCorner(), it->GetLeftTopCorner(), it->GetRightTopCorner());

                v3 = glm::InSegment(p1, it->GetLeftTopCorner(), it->GetRightTopCorner());
                v4 = glm::InSegment(p2, it->GetLeftTopCorner(), it->GetRightTopCorner());

                if (v3 || v4) {
                    glm::vec2 vect = p2 - support.GetRightBottomCorner();
                    float yDist = glm::length(vect);

                    if (yBottomMaxDistance > yDist) yBottomMaxDistance = yDist;
                }
            }
            //top
            else {
                glm::vec2 p1 = glm::ProjectPointOnAxis(support.GetLeftTopCorner(), it->GetLeftBottomCorner(), it->GetRightBottomCorner());
                glm::vec2 p2 = glm::ProjectPointOnAxis(support.GetRightTopCorner(), it->GetLeftBottomCorner(), it->GetRightBottomCorner());

                v3 = glm::InSegment(p1, it->GetLeftBottomCorner(), it->GetRightBottomCorner());
                v4 = glm::InSegment(p2, it->GetLeftBottomCorner(), it->GetRightBottomCorner());

                if (v3 || v4) {
                    glm::vec2 vect = p2 - support.GetRightTopCorner();
                    float yDist = glm::length(vect);

                    if (yTopMaxDistance > yDist) yTopMaxDistance = yDist;
                }
            }
        }

        //Calculate new pos and size of support

        constexpr float epsilon = 0.0005f;

        glm::vec2 oldPos  = support.GetPosition();
        glm::vec2 oldSize = support.GetSize();

        oldPos  -= glm::vec2{xLeftMaxDistance,  yBottomMaxDistance};

        //oldSize.x += xLeftMaxDistance  + xRightMaxDistance  + epsilon;
        //oldSize.y += yTopMaxDistance   + yBottomMaxDistance + epsilon;

        oldSize.x += xLeftMaxDistance  + xRightMaxDistance;
        oldSize.y += yTopMaxDistance   + yBottomMaxDistance;

        glm::vec2 newLeftBottomCorner = oldPos;
        glm::vec2 newRightTopCorner   = oldPos + oldSize;

        if (newRightTopCorner.x > 1) { newRightTopCorner.x = 1; }
        if (newRightTopCorner.y > 1) { newRightTopCorner.y = 1; }

        float xDelta = 0;
        if (newLeftBottomCorner.x < 0) {
            xDelta = std::abs(newLeftBottomCorner.x);
            newLeftBottomCorner.x = 0;
        }
        float yDelta = 0;
        if (newLeftBottomCorner.y < 0) {
            yDelta = std::abs(newLeftBottomCorner.y);
            newLeftBottomCorner.y = 0;
        }

        glm::vec2 newSize = newRightTopCorner;
        newSize.x -= std::abs(oldPos.x);
        newSize.y -= std::abs(oldPos.y);

        newSize.x += xDelta;
        newSize.y += yDelta;

        //newSize += epsilon;

        if (newSize.x > 1) { newSize.x = 1; }
        if (newSize.y > 1) { newSize.y = 1; }

        glm::vec2 newPos = newLeftBottomCorner;

        support.SetPosition(newPos);
        support.SetSize(newSize);

        RecalculateFreeSpace(support);
        RecalculateRectangleNeighbors(support);
    }

//=============================RECTANGLE SETTINGS=============================//

    Rectangle& Window::CreateRectangle(
        const glm::vec2& position,
        const glm::vec2& size) {

        if (position.x < 0) {
            Core::Logger::LogCritical("X position should be positive: " + __LOGERROR__);
            abort();
        }
        if (position.y < 0) {
            Core::Logger::LogCritical("Y position should be positive: " + __LOGERROR__);
            abort();
        }

        if (size.x <= 0) {
            Core::Logger::LogCritical("X size should be higher than zero: " + __LOGERROR__);
            abort();
        }
        if (size.y <= 0) {
            Core::Logger::LogCritical("Y size should be higher than zero: " + __LOGERROR__);
            abort();
        }

        if (position.x > 1) {
            Core::Logger::LogCritical("X position should be normalized: " + __LOGERROR__);
            abort();
        }
        if (position.y > 1) {
            Core::Logger::LogCritical("Y position should be normalized: " + __LOGERROR__);
            abort();
        }
        if (size.x > 1) {
            Core::Logger::LogCritical("X size should be normalized: " + __LOGERROR__);
            abort();
        }
        if (size.y > 1) {
            Core::Logger::LogCritical("Y size should be normalized: " + __LOGERROR__);
            abort();
        }

        _rectangles.emplace_back(std::unique_ptr<Rectangle>(new Rectangle(position, size)));

        RecalculateFreeSpace(*_rectangles.back());
        RecalculateRectangleNeighbors(*_rectangles.back());

        return *_rectangles.back();
    }

    void Window::DestroyRectangle(const size_t index) {
        if (index >= _rectangles.size()) {
            Core::Logger::LogError("Index out of bounds: " + __LOGERROR__);
            return;
        }

        RecalculateFreeSpace(*_rectangles.back());
        RecalculateRectangleNeighbors(*_rectangles.back());
    }

    Rectangle& Window::GetRectangle(size_t index) {
        if (index >= _rectangles.size()) {
            Core::Logger::LogCritical("Index out of bounds: " + __LOGERROR__);
            abort();
        }

        return *_rectangles[index];
    }

    float Window::PushLeftRectEdge(
            const float delta,
            Rectangle& support,
            std::shared_ptr<std::vector<std::pair<Rectangle*, bool>>> checked) {

        bool isHeader = false;

        if (checked == nullptr) {
            isHeader = true;
            checked = std::make_shared<std::vector<std::pair<Rectangle*, bool>>>();
        }
        checked->emplace_back(&support, false);

        auto checkBorders = [](float newPos) {
            float delta = 0;

            if (newPos < 0) {
                delta = std::fabs(newPos);
                newPos = 0;
            }

            return delta;
        };
        auto checkSize = [](float newLeftCorner, float oldRightCorner, float minSize){
            float delta = 0;

            float currentDelta = oldRightCorner - newLeftCorner;

            if (minSize > currentDelta) {
                delta = minSize - currentDelta;
            }

            return delta;
        };


        constexpr float epsilon = 0.0005f;

        //Check if it out of bounds
        float realDeltaSize = delta;

        {
            float newPos = support.GetPosition().x - delta;

            float borderDelta = checkBorders(newPos);
            newPos += borderDelta;

            //float sizeDelta = checkSize(support.GetLeftBottomCorner().x + borderDelta, support.GetRightBottomCorner().x, support._minSize.x);
            float sizeDelta = checkSize(newPos, support.GetRightBottomCorner().x, support._minSize.x);
            realDeltaSize += sizeDelta;

            std::cout << newPos << "  " << support.GetRightBottomCorner().x << std::endl;
        }

        //if real delta < 0
        //take left edge and push it to right -->
        //change left neighbors
        //trying to make it bigger

        //if real delta > 0
        //take left edge and push it to left <--
        //also changing left neighbors
        //trying to make it smaller

        for (auto it: support._leftNeighbors) {
            bool isAvailable = true;

            for (auto & check : *checked) {
                if (it == check.first) {
                    isAvailable = false;
                    break;
                }
            }

            if (isAvailable) {
                float newDelta = PushRightRectEdge(realDeltaSize * -1, *it, checked);
                if(newDelta < realDeltaSize) {
                    realDeltaSize = newDelta;
                }
            }
        }

        if (std::fabs(realDeltaSize) < epsilon) { realDeltaSize = 0; }

        if (realDeltaSize != delta) {
            float shortageDelta = delta - realDeltaSize;

            for (auto it: support._rightNeighbors) {
                bool isAvailable = true;

                for (auto &check: *checked) {
                    if (it == check.first) {
                        isAvailable = false;
                        break;
                    }
                }

                if (isAvailable) {
                    //PushLeftRect(shortageDelta * -1, support, checked);
                    //std::pair<float, float> newDelta = PushLeftRectEdge(shortageDelta, *it, checked);
                    //posDelta = newDelta.first;
                    //if(newDelta < realDelta) {
                    //    realDelta = newDelta;
                    //}
                }
            }
            std::cout << "test" << std::endl;
        }

        if (isHeader) {
            for(auto& it : *checked) {
                if (it.second) {
                    glm::vec2 newSize = it.first->GetSize();
                    newSize.x += -realDeltaSize;

                    it.first->SetSize(newSize);
                }
                else {
                    float oldXRightCorner = it.first->GetRightBottomCorner().x;

                    glm::vec2 newPos = it.first->GetPosition();

                    newPos.x += -realDeltaSize;

                    it.first->SetPosition(newPos);

                   //glm::vec2 newSize = it.first->GetSize();
                   //newSize.x += realDelta;

                   //it.first->SetSize(newSize);

                    float newXRightCorner = it.first->GetRightBottomCorner().x;

                    float errorDelta = newXRightCorner - oldXRightCorner;
                    glm::vec2 newSize = it.first->GetSize();
                    newSize.x += -errorDelta;
                    it.first->SetSize(newSize);
                }
            }
        }

        return -realDeltaSize;
    }




    float Window::PushRightRectEdge(
            const float delta,
            Rectangle& support,
            std::shared_ptr<std::vector<std::pair<Rectangle*, bool>>> checked) {

        bool isHeader = false;

        if (checked == nullptr) {
            isHeader = true;
            checked = std::make_shared<std::vector<std::pair<Rectangle*, bool>>>();
        }

        checked->emplace_back(&support, true);


        auto checkBorders = [](float pos, float size) {
            float delta = 0;
            float rightCorner = pos + size;

            if (rightCorner > 1) {
                delta = 1 - rightCorner;
            }

            return delta;
        };

        auto checkSize = [](float oldLeftCorner, float newRightCorner, float minSize){
            float delta = 0;

            float currentDelta = newRightCorner - oldLeftCorner;

            if (minSize > currentDelta) {
                delta = minSize - currentDelta;
            }

            return delta;
        };

        constexpr float epsilon = 0.0005f;

        //Check if it out of bounds
        float realDeltaSize = delta;

        {
            float newSize = support.GetSize().x + delta;

            float borderDelta = checkBorders(support.GetPosition().x, newSize);
            realDeltaSize -= borderDelta;

            newSize = support.GetRightBottomCorner().x + realDeltaSize;
            float sizeDelta = checkSize(support.GetLeftBottomCorner().x,newSize,support._minSize.x);
            realDeltaSize += sizeDelta;

            //std::cout << "  " << support.GetSize().x << std::endl;
        }

        //if real delta > 0
        //take right edge and push it to right -->
        //also changing right neighbors
        //trying to make it smaller

        //if real delta < 0
        //take right edge and push it to left <--
        //also changing right neighbors
        //trying to make it bigger

        for (auto it: support._rightNeighbors) {
            bool isAvailable = true;

            for (auto & check : *checked) {
                if (it == check.first) {
                    isAvailable = false;
                    break;
                }
            }

            if (isAvailable) {
                float newDelta = PushLeftRectEdge(realDeltaSize * -1, *it, checked);
                if(newDelta < realDeltaSize) {
                    realDeltaSize = newDelta;
                }
            }
        }

        if (std::fabs(realDeltaSize) < epsilon) {
            realDeltaSize = 0;
        }

        if (isHeader) {
            for(auto& it : *checked) {
                if (it.second) {
                    glm::vec2 newSize = it.first->GetSize();
                    newSize.x += realDeltaSize;

                    it.first->SetSize(newSize);
                }
                else {
                    glm::vec2 newPos = it.first->GetPosition();
                    newPos.x += realDeltaSize;

                    it.first->SetPosition(newPos);

                    glm::vec2 newSize = it.first->GetSize();
                    newSize.x += -realDeltaSize;

                    it.first->SetSize(newSize);
                }
            }
        }

        return -realDeltaSize;
    }

    float Window::PushLeftRect (
            float delta,
            Rectangle& support,
            std::shared_ptr<std::vector<std::pair<Rectangle*, bool>>> checked) {

        bool isHeader = false;

        if (checked == nullptr) {
            isHeader = true;
            checked = std::make_shared<std::vector<std::pair<Rectangle*, bool>>>();
        }

        auto checkBorders = [](float pos, float size) {
            float delta = 0;

            if (pos < 0) {
                delta = std::abs(pos);
            }

            if (pos + size > 1) {
                delta = 1 - (pos + size);
            }

            return delta;
        };

        checked->emplace_back(&support, true);

        constexpr float epsilon = 0.0005f;

        //Check if it out of bounds
        float realDeltaPos = delta;

        {
            float newPos = support.GetPosition().x + realDeltaPos;
            float borderDelta = checkBorders(newPos, support.GetSize().x);

            realDeltaPos += borderDelta;
        }

        //push from left to right -->
        if (realDeltaPos > 0) {
            for (auto it: support._rightNeighbors) {
                bool isAvailable = true;

                for (auto & check : *checked) {
                    if (it == check.first) {
                        isAvailable = false;
                        break;
                    }
                }

                if (isAvailable) {
                    float newDelta = PushLeftRect(realDeltaPos, *it, checked);
                    if(newDelta < realDeltaPos) {
                        realDeltaPos = newDelta;
                    }
                }
            }
        }
        //push from left ot left <--
        else if (realDeltaPos < 0) {

        }

        if (std::fabs(realDeltaPos) < epsilon) { realDeltaPos = 0; }

        if (realDeltaPos != delta) {
            float shortageDelta = delta - realDeltaPos;

            //PushLeftRectEdge(shortageDelta * -1, support, checked);
            //std::pair<float, float> newDelta = PushLeftRectEdge(shortageDelta, *it, checked);
            //posDelta = newDelta.first;
            //if(newDelta < realDelta) {
            //    realDelta = newDelta;
            //}
        }

        if (isHeader) {
            for(auto& it : *checked) {
                if (it.second) {

                }
                else {

                }
            }
        }

        return -realDeltaPos;
    }

    void Window::SetRectanglePosition(const glm::vec2& position, const size_t index) {
        if (index >= _rectangles.size()) {
            Core::Logger::LogCritical("Index out of bounds: " + __LOGERROR__);
            return;
        }

        //separate x and y component
        float xTransform = position.x;
        float yTransform = position.y;

        struct Deltas {
            float xLeftDelta = 0, xRightDelta = 0;
            float yTopDelta = 0, yBottomDelta = 0;
        };
        //struct separateDeltas {
        //    //or bottom
        //    float leftDelta = 0;
        //    //or top
        //    float rightDelta = 0;
        //};


        auto checkBorders = [](glm::vec2& pos) {
            Deltas deltas;

            if (pos.x < 0) {
                deltas.xLeftDelta = std::abs(pos.x);
                pos.x = 0;
            }
            if (pos.y < 0) {
                deltas.yBottomDelta = std::abs(pos.y);
                pos.y = 0;
            }

            if (pos.x > 1) {
                deltas.xRightDelta = 1 - pos.x;
                pos.x = 1;
            }
            if (pos.y > 1) {
                deltas.yTopDelta = 1 - pos.y;
                pos.y = 1;
            }

            return deltas;
        };
        auto separateCheckBorders = [](float oldPos, float newPos) {
            float delta = newPos - oldPos;

            if (newPos < 0) {
                delta = 0;
            }
            if (newPos > 1) {
                delta = 0;
            }

            return delta;
        };
        auto separateCheckSize = [](
                float leftCorner, float rightCorner, float pushDelta, float minimumDistance) {

            float delta = 0;
            float newLeftCorner = leftCorner + pushDelta;

            float dist = rightCorner - newLeftCorner;
            float maxAcceptableDelta = dist - minimumDistance;

            if (newLeftCorner > rightCorner) {
                float currDist = 0;

                if (currDist < maxAcceptableDelta) {
                    delta = std::fabs(maxAcceptableDelta - newLeftCorner);
                    return delta;
                }
            }
            else if (dist > maxAcceptableDelta) {
                delta = pushDelta - (dist - maxAcceptableDelta);
                return delta;
            }

            return pushDelta;
        };

        auto changeSize = [](glm::vec2 delta, Rectangle& changes, bool isPushRightEdge) {
            if (isPushRightEdge) {
                glm::vec2 newSize = changes.GetSize();
                newSize += delta;

                changes.SetSize(newSize);
                return;
            }

            glm::vec2 oldPos = changes.GetPosition();
            glm::vec2 newPos = oldPos + delta;

            glm::vec2 oldSize = changes.GetSize();
            glm::vec2 newSize = oldSize - delta;

            changes.SetPosition(newPos);
            changes.SetSize(newSize);
        };

        constexpr float epsilon = 0.0005f;
        auto &support = _rectangles[index];

        //Check if it out of bounds
        glm::vec2 newPos = position;
        checkBorders(newPos);
        glm::vec2 delta = newPos - support->_position;

        auto step = [&separateCheckBorders, &separateCheckSize]
                (float leftCorner, float rightCorner, float delta, float minSize) {

            //first - max found empty space for pushing neighbor
            //second - max found size(in this case: push left edge to the right)
            std::pair<float, float> maximum {0, 0};

            //trying change pos without changing size
            {
                float newRightCorner = rightCorner + delta;
                float neighDelta = separateCheckBorders(rightCorner, newRightCorner);

                maximum.first += neighDelta;
            }

            //trying changing size(in this case: push left edge to the right)
            {
                float neighDeltas = separateCheckSize(
                        leftCorner,
                        rightCorner,
                        delta,
                        minSize);

                maximum.second += neighDeltas;
            }

            return maximum;
        };

        //check xComponent
        if (delta.x != 0) {

            //push left
            if (delta.x < 0) {
                //change left neighbors

                //trying to make smaller right neighbors

                //first - max found empty space for pushing neighbor
                //second - max found size(in this case: push left edge to the right)
                std::pair<float, float> maximum {0, 0};

                for (auto it: support->_leftNeighbors) {
                    maximum = step(it->GetRightBottomCorner().x, it->GetLeftBottomCorner().x, delta.x, it->_minSize.x);

                    changeSize({maximum.second, 0}, *it, true);
                }
            }
            //push right
            else if (delta.x > 0) {
                //change right neighbors

                //trying to make smaller right neighbors

                //first - max found empty space for pushing neighbor
                //second - max found size(in this case: push left edge to the right)
                std::pair<float, float> maximum {0, 0};

                for (auto it: support->_rightNeighbors) {
                    maximum = step(it->GetLeftBottomCorner().x, it->GetRightBottomCorner().x, delta.x, it->_minSize.x);

                   changeSize({maximum.second, 0}, *it, false);
                }

            }
        }

        support->SetPosition(newPos);
    }

    glm::vec2 Window::GetRectangleSize(const size_t index) const {
        if (index >= _rectangles.size()) {
            Core::Logger::LogCritical("Index out of bounds: " + __LOGERROR__);
            return {0,0};
        }

        return _rectangles[index]->GetSize();
    }

    glm::vec2 Window::GetRectanglePosition(const size_t index) const {
        if (index >= _rectangles.size()) {
            Core::Logger::LogCritical("Index out of bounds: " + __LOGERROR__);
            return {0,0};
        }

        return _rectangles[index]->GetPosition();
    }

    bool Window::CheckRectangleExist(const size_t index) const {
        if (index >= _rectangles.size()) {
            return false;
        }
        return true;
    }
//=============================RECTANGLE SETTINGS=============================//
}
