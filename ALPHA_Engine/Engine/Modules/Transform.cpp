#include "Transform.h"

Transform::Transform() {
	Transform::_transformMatrix = glm::mat4x4(1.0f);
}
Transform::~Transform() {

}
