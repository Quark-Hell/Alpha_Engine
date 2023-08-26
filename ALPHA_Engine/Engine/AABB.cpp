#include "AABB.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

AABB::AABB() {
#ifdef _DEBUG
    AABB::CreateAABB();
#endif // _DEBUG
    std::cout << "create\n";
}

AABB::AABB(
	float minX, float maxX,
	float minY, float maxY,
	float minZ, float maxZ) {

    AABB::SetSize(minX, maxX, minY, maxY, minZ, maxZ);

    std::cout << "create\n";
}

AABB::~AABB() {

}

#ifdef _DEBUG
void AABB::CreateAABB() {
#ifdef _DEBUG

    AABB::_AABBvertex.clear();
    AABB::_AABBindices.clear();

    AABB::_AABBvertex.reserve(24);
    AABB::_AABBindices.reserve(20);
    
    //front side
    AABB::_AABBvertex.push_back(-0.5f);
    AABB::_AABBvertex.push_back(-0.5f);
    AABB::_AABBvertex.push_back(0.5f);
    
    AABB::_AABBvertex.push_back(-0.5f);
    AABB::_AABBvertex.push_back(0.5f);
    AABB::_AABBvertex.push_back(0.5f);
    
    AABB::_AABBvertex.push_back(0.5f);
    AABB::_AABBvertex.push_back(0.5f);
    AABB::_AABBvertex.push_back(0.5f);
    
    AABB::_AABBvertex.push_back(0.5f);
    AABB::_AABBvertex.push_back(-0.5f);
    AABB::_AABBvertex.push_back(0.5f);
    
    //back side
    AABB::_AABBvertex.push_back(-0.5f);
    AABB::_AABBvertex.push_back(-0.5f);
    AABB::_AABBvertex.push_back(-0.5f);
    
    AABB::_AABBvertex.push_back(-0.5f);
    AABB::_AABBvertex.push_back(0.5f);
    AABB::_AABBvertex.push_back(-0.5f);
    
    AABB::_AABBvertex.push_back(0.5f);
    AABB::_AABBvertex.push_back(0.5f);
    AABB::_AABBvertex.push_back(-0.5f);
    
    AABB::_AABBvertex.push_back(0.5f);
    AABB::_AABBvertex.push_back(-0.5f);
    AABB::_AABBvertex.push_back(-0.5f);
      
    
    AABB::_AABBindices.push_back(0);
    AABB::_AABBindices.push_back(1);
    AABB::_AABBindices.push_back(2);
    AABB::_AABBindices.push_back(3);
    
    AABB::_AABBindices.push_back(0);
    AABB::_AABBindices.push_back(4);
    AABB::_AABBindices.push_back(7);
    AABB::_AABBindices.push_back(3);
    
    AABB::_AABBindices.push_back(3);
    AABB::_AABBindices.push_back(2);
    AABB::_AABBindices.push_back(6);
    AABB::_AABBindices.push_back(7);
    
    AABB::_AABBindices.push_back(7);
    AABB::_AABBindices.push_back(6);
    AABB::_AABBindices.push_back(5);
    AABB::_AABBindices.push_back(4);
    
    AABB::_AABBindices.push_back(4);
    AABB::_AABBindices.push_back(5);
    AABB::_AABBindices.push_back(5);
    AABB::_AABBindices.push_back(1);
#endif 
}
#endif // _DEBUG

void AABB::SetSize(
    float minX, float maxX,
    float minY, float maxY,
    float minZ, float maxZ){
 
#ifdef _DEBUG
    AABB::CreateAABB();

    glm::mat4x4 transformMat(1.0f);
    
    Vector3 nowScale = Vector3(1, 1, 1);
    Vector3 setScale = Vector3(maxX - minX, maxY - minY, maxZ - minZ);

    AABB::_scale = setScale;
    
    Vector3 delta = nowScale / setScale;
    transformMat = glm::scale(transformMat, glm::vec3(1 / delta.X, 1 / delta.Y, 1 / delta.Z));

    for (size_t jt = 0; jt < _AABBvertex.size(); jt += 3)
    {
        glm::vec4 buf(AABB::_AABBvertex[jt], AABB::_AABBvertex[jt + 1], AABB::_AABBvertex[jt + 2], 1);
    
        glm::vec4 res;
        res = transformMat * buf;
        AABB::_AABBvertex[jt + 0] = res.x;
        AABB::_AABBvertex[jt + 1] = res.y;
        AABB::_AABBvertex[jt + 2] = res.z;
    }
#endif // _DEBUG

    AABB::_minX = minX;	AABB::_maxX = maxX;
    AABB::_minY = minY;	AABB::_maxY = maxY;
    AABB::_minZ = minZ;	AABB::_maxZ = maxZ;
}

float AABB::GetMinX() {
    return AABB::_minX;
}
float AABB::GetMaxX() {
    return AABB::_maxX;
}
float AABB::GetMinY() {
    return AABB::_minY;
}
float AABB::GetMaxY() {
    return AABB::_maxY;
}
float AABB::GetMinZ() {
    return AABB::_minZ;
}
float AABB::GetMaxZ() {
    return AABB::_maxZ;
}

void AABB::GetSize(float& minX, float& maxX, float& minY, float& maxY, float& minZ, float& maxZ) {
    minX = AABB::_minX;
    maxX = AABB::_maxX;

    minY = AABB::_minY;
    maxY = AABB::_maxY;

    minZ = AABB::_minZ;
    maxZ = AABB::_maxZ;
}

Vector3 AABB::GetAABBPosition() {
    return { (AABB::_maxX + AABB::_minX) * 0.5f, (AABB::_maxY + AABB::_minY) * 0.5f, (AABB::_maxZ + AABB::_minZ) * 0.5f };

}

void AABB::UpdateAABB(const float* vertex, float vertexCount) {
    float minX = FLT_MAX,  minY = FLT_MAX,  minZ = FLT_MAX;
    float maxX = -FLT_MAX, maxY = -FLT_MAX, maxZ = -FLT_MAX;

    for (size_t i = 0; i < vertexCount * 3; i += 3)
    {
        //Min
        if (minX > vertex[i + 0])
            minX = vertex[i + 0];

        if (minY > vertex[i + 1])
            minY = vertex[i + 1];

        if (minZ > vertex[i + 2])
            minZ = vertex[i + 2];


        //Max
        if (maxX < vertex[i + 0])
            maxX = vertex[i + 0];

        if (maxY < vertex[i + 1])
            maxY = vertex[i + 1];

        if (maxZ < vertex[i + 2])
            maxZ = vertex[i + 2];
    }

    AABB::SetSize(minX, maxX, minY, maxY, minZ, maxZ);
}