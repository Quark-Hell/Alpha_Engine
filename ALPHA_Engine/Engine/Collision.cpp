#include "Collision.h"
#include <unordered_map>
#include <chrono>
#include <queue>


inline bool Collision::CreateCollision(std::string link) {
    Assimp::Importer importer;
    std::string path = std::filesystem::current_path().string() + link.c_str();

    //TODO: Check if fbx
    const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate);
    aiMesh* mesh = s->mMeshes[0];

    GeneralCollider->Points.clear();
    GeneralCollider->Normals.clear();

    for (std::uint32_t it = 0; it < mesh->mNumVertices; it++) {
        Vector3 point;
        Vector3 normal;

        if (mesh->HasPositions()) {
            point.X = mesh->mVertices[it].x;
            point.Y = mesh->mVertices[it].y;
            point.Z = mesh->mVertices[it].z;
        }

        if (mesh->HasNormals()) {
            normal.X = mesh->mNormals[it].x;
            normal.Y = mesh->mNormals[it].y;
            normal.Z = mesh->mNormals[it].z;
        }

        GeneralCollider->Points.push_back(point);
        GeneralCollider->Normals.push_back(normal);
    }

    SeparateCollision();

    return true;
}

inline bool Collision::SeparateCollision() {
    struct VertInfo
    {
        Vector3* Point;
        unsigned int TriangleID;
    };

    VertInfo vert;
    std::unordered_map<std::string, VertInfo> vertMap;
    std::vector<bool> triangleBool;

    const int arr_len = 3;
    float edgeArr[arr_len];

    std::string hash;
    hash.resize(arr_len * sizeof(float));

    Graph graph{ unsigned int (GeneralCollider->Points.size() / 3)};

    unsigned int sizeBeforeInsert;

    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

    //Create graph
    for (size_t it = 0; it <= GeneralCollider->Points.size() - 1; it++)
    {
        vert.Point = &GeneralCollider->Points[it];
        vert.TriangleID = it / 3;

        edgeArr[0] = { vert.Point->X };
        edgeArr[1] = { vert.Point->Y };
        edgeArr[2] = { vert.Point->Z };

        sizeBeforeInsert = vertMap.size();

        //create hash
        memcpy((char*)hash.data(), edgeArr, arr_len * sizeof(float));

        //insert hash
        std::pair<std::string, VertInfo> p(hash, vert);
        vertMap.insert(p);

        //chech if hash map not changed size after insert hash
        //is not changed => found same edges => found adjacent triangles
        if (sizeBeforeInsert == vertMap.size()) {
            unsigned int TriangleID = vertMap.find(hash)->second.TriangleID;
            graph.AddEdge(TriangleID, vert.TriangleID);
            graph.AddEdge(vert.TriangleID, TriangleID);
        }
    }

    triangleBool.resize(graph.GetAdjListSize());
    Collision::PrimitivesCollider.push_back(new Collider);
    std::vector<std::vector<int>> separatedMesh;

    while (true) {
        int notConnected = -1;
        //Searches first triangle that does not belong to separated mesh
        for (size_t i = 0; i < triangleBool.size(); i++)
        {
            if (triangleBool[i] == false) {
                notConnected = i;
                break;
            }
        }
        if (notConnected == -1)
            break;

        separatedMesh.resize(separatedMesh.size() + 1);
        graph.BFS(notConnected, &separatedMesh[separatedMesh.size() - 1]);

        for (size_t i = 0; i < separatedMesh[separatedMesh.size() - 1].size(); i++)
        {   
            triangleBool[separatedMesh[separatedMesh.size() - 1][i]] = true;
        }
    }

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast	<std::chrono::milliseconds>(stop - start);

    std::cout << "Time taken by function: "
        << duration.count() << " milliseconds" << std::endl;

    return true;
}


inline bool Collision::CreateConvexFromÑoncave(std::string link) {

}

inline void Graph::AddEdge(int Src, int Dest) {
    Graph::adjLists[Src].push_back(Dest);
}

inline void Graph::DFS(int StartVertex, std::vector<int> *Output) {
    Graph::visited[StartVertex] = true;
    Output->push_back(StartVertex);

    for (size_t i = 0; i < Graph::adjLists[StartVertex].size(); i++)
    {
        if (!Graph::visited[Graph::adjLists[StartVertex][i]]) {
            Graph::DFS(Graph::adjLists[StartVertex][i], Output);
        }
    }
}

inline void Graph::BFS(int StartVertex, std::vector<int>* Output) {
    std::queue<int> q;
    visited[StartVertex] = true;
    q.push(StartVertex);

    while (!q.empty()) {
        int current = q.front();
        Output->push_back(current);
        q.pop();

        for (int i = 0; i < adjLists[current].size(); i++) {
            if (!visited[adjLists[current][i]]) {
                visited[adjLists[current][i]] = true;
                q.push(adjLists[current][i]);
            }
        }
    }
}

inline Graph::Graph(unsigned int size) {
    Graph::adjLists.resize(size);
    Graph::visited.resize(size);
}

inline unsigned int Graph::GetAdjListSize() {
    return Graph::adjLists.size();
}