#include <gtest/gtest.h>
#include <random>


#include "Core/Resources/Geometry.h"
#include "Modules.h"

TEST(CoreTest, RandomTransformTest) {
    // Fixed seed for reproducibility
    std::mt19937 rng(12345);
    std::uniform_real_distribution<float> posDist(-100.0f, 100.0f);
    std::uniform_real_distribution<float> rotDist(0.0f, 360.0f);
    std::uniform_real_distribution<float> scaleDist(0.1f, 50.0f);

    // Generate random transform
    glm::vec3 randomPos(posDist(rng), posDist(rng), posDist(rng));
    glm::vec3 randomRot(rotDist(rng), rotDist(rng), rotDist(rng));
    glm::vec3 randomScale(scaleDist(rng), scaleDist(rng), scaleDist(rng));

    // Create object and apply transformations
    auto& cube = Core::Factory::CreateObject();
    cube.transform.AddPosition(randomPos.x, randomPos.y, randomPos.z);
    cube.transform.AddRotation(randomRot.x, randomRot.y, randomRot.z);
    cube.transform.SetScale(randomScale.x, randomScale.y, randomScale.z);

    // Check position
    EXPECT_FLOAT_EQ(cube.transform.GetPosition().x, randomPos.x);
    EXPECT_FLOAT_EQ(cube.transform.GetPosition().y, randomPos.y);
    EXPECT_FLOAT_EQ(cube.transform.GetPosition().z, randomPos.z);

    // Check scale
    EXPECT_FLOAT_EQ(cube.transform.GetScale().x, randomScale.x);
    EXPECT_FLOAT_EQ(cube.transform.GetScale().y, randomScale.y);
    EXPECT_FLOAT_EQ(cube.transform.GetScale().z, randomScale.z);

    // Check transform matrix
    glm::mat4 mat = cube.transform.GetTransformMatrix();

    // Check translation: last column
    EXPECT_NEAR(mat[3][0], randomPos.x, 1e-5f);
    EXPECT_NEAR(mat[3][1], randomPos.y, 1e-5f);
    EXPECT_NEAR(mat[3][2], randomPos.z, 1e-5f);

    // Check scale: length of basis vectors
    glm::vec3 matScale(
        glm::length(glm::vec3(mat[0])),
        glm::length(glm::vec3(mat[1])),
        glm::length(glm::vec3(mat[2]))
    );

    EXPECT_NEAR(matScale.x, randomScale.x, 1e-5f);
    EXPECT_NEAR(matScale.y, randomScale.y, 1e-5f);
    EXPECT_NEAR(matScale.z, randomScale.z, 1e-5f);

    // Check rotation: directions of local axes (normalized to ignore scale)
    glm::vec3 localX = glm::normalize(glm::vec3(mat[0]));
    glm::vec3 localY = glm::normalize(glm::vec3(mat[1]));
    glm::vec3 localZ = glm::normalize(glm::vec3(mat[2]));

    // Optional: just check that axes are normalized and orthogonal
    EXPECT_NEAR(glm::length(localX), 1.0f, 1e-5f);
    EXPECT_NEAR(glm::length(localY), 1.0f, 1e-5f);
    EXPECT_NEAR(glm::length(localZ), 1.0f, 1e-5f);

    EXPECT_NEAR(glm::dot(localX, localY), 0.0f, 1e-5f);
    EXPECT_NEAR(glm::dot(localX, localZ), 0.0f, 1e-5f);
    EXPECT_NEAR(glm::dot(localY, localZ), 0.0f, 1e-5f);
}

TEST(CoreObjectTest, NameTest) {
    auto& cube = Core::Factory::CreateObject();

    // Optional: check initial value
    EXPECT_EQ(cube.GetName(), "Undefined");

    // Set a name
    std::string testName = "MyCube";
    cube.SetName(testName);

    // Verify that GetName returns the correct name
    EXPECT_EQ(cube.GetName(), testName);

    // Change the name again
    std::string anotherName = "AnotherObject";
    cube.SetName(anotherName);

    // Verify the new name
    EXPECT_EQ(cube.GetName(), anotherName);
}


TEST(CoreObjectTest, CreateAndRemoveTest) {
    // Create a new object
    Core::GameObject& obj = Core::Factory::CreateObject();

    // Remove the object
    bool removed = Core::Factory::RemoveObject(&obj);

    // Verify removal succeeded
    EXPECT_TRUE(removed);

    // Optional: try removing again — should return false if object was already removed
    bool removedAgain = Core::Factory::RemoveObject(&obj);
    EXPECT_FALSE(removedAgain);
}

TEST(CoreObjectTest, AddComponentTest) {
    // Create object
    auto& obj = Core::Factory::CreateObject();

    // Initially, the object should have 0 components
    EXPECT_EQ(obj.GetCountOfComponents(), 0);

    // Create a Geometry component
    Core::Geometry geom;

    // Add component
    bool added = obj.AddComponent(geom);

    // Verify that AddComponent returned true
    EXPECT_TRUE(added);

    // Verify that the component count increased
    EXPECT_EQ(obj.GetCountOfComponents(), 1);

    // Add another component
    Core::Geometry geom2;
    obj.AddComponent(geom2);

    // Component count should now be 2
    EXPECT_EQ(obj.GetCountOfComponents(), 2);

    // Check that adding the same component again fails (depends on implementation)
    bool addedAgain = obj.AddComponent(geom);
    EXPECT_FALSE(addedAgain);
}