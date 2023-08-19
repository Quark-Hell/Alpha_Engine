#include "AABB.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

AABB::AABB(
	float minX, float maxX,
	float minY, float maxY,
	float minZ, float maxZ) {

#ifdef _DEBUG
    AABB::CreateAABB();
    AABB::SetSize(minX, maxX, minY, maxY, minZ, maxZ);
#endif // _DEBUG

    std::cout << "create\n";
}

AABB::~AABB() {

}

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

void AABB::SetSize(
    float minX, float maxX,
    float minY, float maxY,
    float minZ, float maxZ){
 
#ifdef _DEBUG
    glm::mat4x4 transformMat(1.0f);
    
    Vector3 nowScale = Vector3(MaxX - MinX, MaxY - MinY, MaxZ - MinZ);
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

    AABB::MinX = minX;	AABB::MaxX = maxX;
    AABB::MinY = minY;	AABB::MaxY = maxY;
    AABB::MinZ = minZ;	AABB::MaxZ = maxZ;
}

void AABB::UpdateAABB(const float* vertex, float vertexCount) {
#ifdef _DEBUG
    float minX = 0, minY = 0, minZ = 0;
    float maxX = 0, maxY = 0, maxZ = 0;

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
#endif // _DEBUG

#ifdef  NDEBUG
    for (size_t i = 0; i < vertexCount * 3; i += 3)
    {
        //Min
        if (AABB::MinX > vertex[i + 0])
            AABB::MinX = vertex[i + 0];

        if (AABB::MinY > vertex[i + 1])
            AABB::MinY = vertex[i + 1];

        if (AABB::MinZ > vertex[i + 2])
            AABB::MinZ = vertex[i + 2];


        //Max
        if (AABB::MaxX < vertex[i + 0])
            AABB::MaxX = vertex[i + 0];

        if (AABB::MaxY < vertex[i + 1])
            AABB::MaxY = vertex[i + 1];

        if (AABB::MaxZ < vertex[i + 2])
            AABB::MaxZ = vertex[i + 2];
    }
#endif //  NDEBUG
}