#include "Collision.h"

#include "World.h"
#include "Modules/Physics.h"
#include "Object.h"

inline bool Simplex::SameDirection(const Vector3& direction, const Vector3& ao) {
    return Vector3::DotProduct(direction,ao) > 0;
}

//Triangle case
inline void Simplex::UpdateSimplex3(Simplex& simplex, int& simp_dim, Vector3& search_dir) {
    /* Required winding order:
    //  b
    //  | \
    //  |   \
    //  |    a
    //  |   /
    //  | /
    //  c
    */
    Vector3 n = Vector3::CrossProduct (simplex[1].first - simplex[0].first, simplex[2].first - simplex[0].first); //triangle's normal
    Vector3 AO = -simplex._points[0].first; //direction to origin

    //Determine which feature is closest to origin, make that the new simplex

    simp_dim = 2;
    if (Vector3::DotProduct(Vector3::CrossProduct(simplex[1].first - simplex[0].first, n), AO) > 0) { //Closest to edge AB    
        simplex._points[2] = simplex._points[0];
        //simp_dim = 2;
        search_dir = Vector3::CrossProduct(Vector3::CrossProduct(simplex[1].first - simplex[0].first, AO), simplex[1].first - simplex[0].first);
        return;
    }
    if (Vector3::DotProduct(Vector3::CrossProduct(n, simplex[2].first - simplex[0].first), AO) > 0) { //Closest to edge AC
        simplex._points[1] = simplex._points[0];
        //simp_dim = 2;
        search_dir = Vector3::CrossProduct(Vector3::CrossProduct(simplex[2].first - simplex[0].first, AO), simplex[2].first - simplex[0].first);
        return;
    }

    simp_dim = 3;
    if (Vector3::DotProduct(n, AO) > 0) { //Above triangle
        simplex._points[3] = simplex._points[2];
        simplex._points[2] = simplex._points[1];
        simplex._points[1] = simplex._points[0];
        //simp_dim = 3;
        search_dir = n;
        return;
    }
    //else //Below triangle
    simplex._points[3] = simplex._points[1];
    simplex._points[1] = simplex._points[0];
    //simp_dim = 3;
    search_dir = -n;
    return;
}

//Tetrahedral case
inline bool Simplex::UpdateSimplex4(Simplex& simplex, int& simp_dim, Vector3& search_dir) {
    // a is peak/tip of pyramid, BCD is the base (counterclockwise winding order)
    //We know a priori that origin is above BCD and below a

    //Get normals of three new faces
    Vector3 ABC = Vector3::CrossProduct(simplex[1].first - simplex[0].first, simplex[2].first - simplex[0].first);
    Vector3 ACD = Vector3::CrossProduct(simplex[2].first - simplex[0].first, simplex[3].first - simplex[0].first);
    Vector3 ADB = Vector3::CrossProduct(simplex[3].first - simplex[0].first, simplex[1].first - simplex[0].first);

    Vector3 AO = -simplex._points[0].first; //dir to origin
    simp_dim = 3; //hoisting this just cause

    if (Vector3::DotProduct(ABC, AO) > 0) { //In front of ABC
        simplex._points[3] = simplex._points[2];
        simplex._points[2] = simplex._points[1];
        simplex._points[1] = simplex._points[0];
        search_dir = ABC;
        return false;
    }
    if (Vector3::DotProduct(ACD, AO) > 0) { //In front of ACD
        simplex._points[1] = simplex._points[0];
        search_dir = ACD;
        return false;
    }
    if (Vector3::DotProduct(ADB, AO) > 0) { //In front of ADB
        simplex._points[2] = simplex._points[3];
        simplex._points[3] = simplex._points[1];
        simplex._points[1] = simplex._points[0];
        search_dir = ADB;
        return false;
    }

    //else inside tetrahedron; enclosed!
    return true;
}

inline Collider::Collider() {
    Collider::Rename("Collider");
}
inline bool Collider::CreateConvexFromÑoncave(std::string link) {

}

inline CollisionInfo Collider::GetCollisionInfo() {
    return Collider::collisionInfo;
}

/*Maybe need refactoring*/
inline void Collision::CollisionLoop() {
    //Clear collision Info
    for (size_t it = 0; it < World::ObjectsOnScene.size() - 1; it++)
    {
        for (size_t jt = 0; jt < World::ObjectsOnScene[it]->GetCountOfModules(); jt++)
        {
            Collider* collider = dynamic_cast<Collider*>(World::ObjectsOnScene[it]->GetModuleByIndex(jt));

            if (collider != nullptr && collider->GetName() == "Collider") {
                collider->collisionInfo.HasCollision = false;
            }
        }
    }


    for (size_t it = 0; it < World::ObjectsOnScene.size()-1; it++)
    {
        for (size_t jt = 0; jt < World::ObjectsOnScene[it]->GetCountOfModules(); jt++)
        {
            Collider* colliderA = dynamic_cast<Collider*>(World::ObjectsOnScene[it]->GetModuleByIndex(jt));
            for (size_t kt = 1; kt < World::ObjectsOnScene.size(); kt++)
            {
                for (size_t mt = 0; mt < World::ObjectsOnScene[kt]->GetCountOfModules(); mt++)
                {
                    Collider* colliderB = dynamic_cast<Collider*>(World::ObjectsOnScene[kt]->GetModuleByIndex(mt));
                    
                    if (colliderA != nullptr && colliderA->GetName() == "Collider" && colliderB != nullptr && colliderB->GetName() == "Collider" && colliderA != colliderB) {
                        Collision::ResolveCollision(*colliderA, *colliderB);
                    }
                }
            }
        }
    }

}

inline Vector3 Collision::Support(Collider& colliderA, Collider& colliderB, Vector3 direction) 
{
    return colliderA.FindFurthestPoint(direction)
        - colliderB.FindFurthestPoint(-direction);
}

inline bool Collision::GJK(Collider& colliderA, Collider& colliderB, Simplex& simplex) {
    Vector3 search_dir = Support(colliderA, colliderB, { 1,0,0 });

    //Get initial point for simplex
    simplex[2].second = search_dir;
    simplex[2].first = Support(colliderA, colliderB, search_dir);
    search_dir = -simplex._points[2].first; //search in direction of origin


    //Get second point for a line segment simplex
    simplex[1].second = search_dir;
    simplex[1].first = Support(colliderA, colliderB, search_dir);

    if (Vector3::DotProduct(simplex[1].first, search_dir) < 0) { return false; }//we didn't reach the origin, won't enclose it

    search_dir = Vector3::CrossProduct(Vector3::CrossProduct(simplex[2].first - simplex[1].first, -simplex[1].first), simplex[2].first - simplex[1].first); //search perpendicular to line segment towards origin
    if (search_dir == Vector3(0, 0, 0)) { //origin is on this line segment
        //Apparently any normal search vector will do?
        search_dir = Vector3::CrossProduct(simplex[2].first - simplex[1].first, Vector3(1, 0, 0)); //normal with x-axis
        if (search_dir == Vector3(0, 0, 0)) search_dir = Vector3::CrossProduct(simplex[2].first - simplex[1].first, Vector3(0, 0, -1)); //normal with z-axis
    }
    int simp_dim = 2; //simplex dimension

    for (int it = 0; it < Collision::GJKaccurate; it++)
    {
        simplex[0].second = search_dir;
        simplex[0].first = Support(colliderA, colliderB, search_dir);
        if (Vector3::DotProduct(simplex[0].first, search_dir) < 0) { return false; }//we didn't reach the origin, won't enclose it

        simp_dim++;
        if (simp_dim == 3) {
            Simplex::UpdateSimplex3(simplex, simp_dim, search_dir);
        }
        else if (Simplex::UpdateSimplex4(simplex, simp_dim, search_dir)) {
            std::cout << "true" << std::endl;
            return true;
        }
    }
    std::cout << "false" << std::endl;
    return false;
}
inline CollisionInfo Collision::EPA(Simplex& simplex, Collider& colliderA, Collider& colliderB, Vector3 movVector)
{
    const unsigned int maxNumFaces = 256;
    const unsigned int maxNumLooseEdges = 128;
    const unsigned int maxNumInterations = 256;
    const float tolerance = 0.0001;

    CollisionInfo colInfo;

    std::pair<Vector3, Vector3> faces[maxNumFaces][4]; //Array of faces, each with 3 verts and a normal

    Vector3 findDirection[2][3];

    //Init with final simplex from GJK
    faces[0][0] = simplex[0];
    faces[0][1] = simplex[1];
    faces[0][2] = simplex[2];
    faces[0][3].first = Vector3::GetNormalize(Vector3::CrossProduct(simplex[1].first - simplex[0].first, simplex[2].first - simplex[0].first)); //ABC
    faces[1][0] = simplex[0];
    faces[1][1] = simplex[2];
    faces[1][2] = simplex[3];
    faces[1][3].first = Vector3::GetNormalize(Vector3::CrossProduct(simplex[2].first - simplex[0].first, simplex[3].first - simplex[0].first)); //ACD
    faces[2][0] = simplex[0];
    faces[2][1] = simplex[3];
    faces[2][2] = simplex[1];
    faces[2][3].first = Vector3::GetNormalize(Vector3::CrossProduct(simplex[3].first - simplex[0].first, simplex[1].first - simplex[0].first)); //ADB
    faces[3][0] = simplex[1];
    faces[3][1] = simplex[3];
    faces[3][2] = simplex[2];
    faces[3][3].first = Vector3::GetNormalize(Vector3::CrossProduct(simplex[3].first - simplex[1].first, simplex[2].first - simplex[1].first)); //BDC

    int num_faces = 4;
    int closest_face;

    for (int iterations = 0; iterations < maxNumInterations; iterations++) {
        //Find face that's closest to origin
        float min_dist = Vector3::DotProduct(faces[0][0].first, faces[0][3].first);
        closest_face = 0;
        for (int i = 1; i < num_faces; i++) {
            float dist = Vector3::DotProduct(faces[i][0].first, faces[i][3].first);
            if (dist < min_dist) {
                min_dist = dist;
                closest_face = i;
            }
        }

        //search normal to face that's closest to origin
        Vector3 search_dir = faces[closest_face][3].first;
        Vector3 p = Support(colliderA, colliderB, search_dir);

        if (Vector3::DotProduct(p, search_dir) - min_dist < tolerance) {
            //Convergence (new point is not significantly further from origin)
            Vector3 points[3][2];
            points[0][0] = colliderA.FindFurthestPoint(faces[closest_face][0].second);
            points[0][1] = colliderB.FindFurthestPoint(-faces[closest_face][0].second);

            points[1][0] = colliderA.FindFurthestPoint(faces[closest_face][1].second);
            points[1][1] = colliderB.FindFurthestPoint(-faces[closest_face][1].second);

            points[2][0] = colliderA.FindFurthestPoint(faces[closest_face][2].second);
            points[2][1] = colliderB.FindFurthestPoint(-faces[closest_face][2].second);

            Vector3 norm = Vector3::GetNormalize(Vector3::CrossProduct(points[1][1] - points[0][1], points[2][1] - points[0][1]));

            //std::pair<Vector3, float> v1 = Vector3::XZ(points[0][0], points[0][1], points[1][1], points[2][1]);
            //std::pair<Vector3, float> v2 = Vector3::XZ(points[1][0], points[0][1], points[1][1], points[2][1]);
            //std::pair<Vector3, float> v3 = Vector3::XZ(points[2][0], points[0][1], points[1][1], points[2][1]);

            Vector3 vec1 = Vector3::project(points[0][0], points[0][1], points[1][1], points[2][1], movVector) - points[0][0];
            Vector3 vec2 = Vector3::project(points[1][0], points[0][1], points[1][1], points[2][1], movVector) - points[1][0];
            Vector3 vec3 = Vector3::project(points[2][0], points[0][1], points[1][1], points[2][1], movVector) - points[2][0];

            float p1 = Vector3::GetMagnitude(vec1);
            float p2 = Vector3::GetMagnitude(vec2);
            float p3 = Vector3::GetMagnitude(vec3);

            if (p1 > 0.19 && p2 > 0.19 && p3 > 0.19) {
                float p2 = Vector3::GetMagnitude(vec2);
            }

            if (p1 <= p2 && p1 <= p3) {
                colInfo.PenetrationDepth = -p1;
                colInfo.Normal = Vector3::GetNormalize(vec1);
            }
            else if (p2 <= p1 && p2 <= p3) {
                colInfo.PenetrationDepth = -p2;
                colInfo.Normal = Vector3::GetNormalize(vec2);
            }
            else {
                colInfo.PenetrationDepth = -p3;
                colInfo.Normal = Vector3::GetNormalize(vec3);
            }
           
            //colInfo.PenetrationDepth = Vector3::DotProduct(p, search_dir);
            //colInfo.Normal = Vector3::GetNormalize(faces[closest_face][3].first);
            colInfo.HasCollision = true;

            return colInfo; //dot vertex with normal to resolve collision along normal!
        }

        std::pair<Vector3, Vector3> loose_edges[maxNumLooseEdges][2]; //keep track of edges we need to fix after removing faces
        int num_loose_edges = 0;

        //Find all triangles that are facing p
        for (int i = 0; i < num_faces; i++)
        {
            if (Vector3::DotProduct(faces[i][3].first, p - faces[i][0].first) > 0) //triangle i faces p, remove it
            {
                //Add removed triangle's edges to loose edge list.
                //If it's already there, remove it (both triangles it belonged to are gone)
                for (int j = 0; j < 3; j++) //Three edges per face
                {
                    std::pair<Vector3, Vector3> current_edge[2] = { faces[i][j], faces[i][(j + 1) % 3] };
                    bool found_edge = false;
                    for (int k = 0; k < num_loose_edges; k++) //Check if current edge is already in list
                    {
                        if (loose_edges[k][1] == current_edge[0] && loose_edges[k][0] == current_edge[1]) {
                            //Edge is already in the list, remove it
                            //THIS ASSUMES EDGE CAN ONLY BE SHARED BY 2 TRIANGLES (which should be true)
                            //THIS ALSO ASSUMES SHARED EDGE WILL BE REVERSED IN THE TRIANGLES (which 
                            //should be true provided every triangle is wound CCW)
                            loose_edges[k][0] = loose_edges[num_loose_edges - 1][0]; //Overwrite current edge
                            loose_edges[k][1] = loose_edges[num_loose_edges - 1][1]; //with last edge in list
                            num_loose_edges--;
                            found_edge = true;
                            k = num_loose_edges; //exit loop because edge can only be shared once
                        }
                    }//endfor loose_edges

                    if (!found_edge) { //add current edge to list
                        // assert(num_loose_edges<EPA_MAX_NUM_LOOSE_EDGES);
                        if (num_loose_edges >= maxNumLooseEdges) break;
                        loose_edges[num_loose_edges][0] = current_edge[0];
                        loose_edges[num_loose_edges][1] = current_edge[1];
                        num_loose_edges++;
                    }
                }

                //Remove triangle i from list
                faces[i][0] = faces[num_faces - 1][0];
                faces[i][1] = faces[num_faces - 1][1];
                faces[i][2] = faces[num_faces - 1][2];
                faces[i][3] = faces[num_faces - 1][3];
                num_faces--;
                i--;
            }//endif p can see triangle i
        }//endfor num_faces

        //Reconstruct polytope with p added
        for (int i = 0; i < num_loose_edges; i++)
        {
            // assert(num_faces<EPA_MAX_NUM_FACES);
            if (num_faces >= maxNumFaces) break;
            faces[num_faces][0] = loose_edges[i][0];
            faces[num_faces][1] = loose_edges[i][1];
            faces[num_faces][2] = {p, search_dir };
            faces[num_faces][3].first = Vector3::GetNormalize(Vector3::CrossProduct(loose_edges[i][0].first - loose_edges[i][1].first, loose_edges[i][0].first - p));

            //Check for wrong normal to maintain CCW winding
            float bias = 0.00001; //in case dot result is only slightly < 0 (because origin is on face)
            if (Vector3::DotProduct(faces[num_faces][0].first, faces[num_faces][3].first) + bias < 0) {
                std::pair<Vector3, Vector3> temp = faces[num_faces][0];
                faces[num_faces][0] = faces[num_faces][1];
                faces[num_faces][1] = temp;
                faces[num_faces][3].first = -faces[num_faces][3].first;
            }
            num_faces++;
        }
    } //End for iterations
    printf("EPA did not converge\n");

    Vector3 points[3][2];
    points[0][0] = colliderA.FindFurthestPoint(faces[closest_face][0].second);
    points[0][1] = colliderB.FindFurthestPoint(-faces[closest_face][0].second);

    points[1][0] = colliderA.FindFurthestPoint(faces[closest_face][1].second);
    points[1][1] = colliderB.FindFurthestPoint(-faces[closest_face][1].second);

    points[2][0] = colliderA.FindFurthestPoint(faces[closest_face][2].second);
    points[2][1] = colliderB.FindFurthestPoint(-faces[closest_face][2].second);

    //Return most recent closest point
    colInfo.Normal = Vector3::GetNormalize(faces[closest_face][3].first);
    colInfo.PenetrationDepth = Vector3::DotProduct(faces[closest_face][0].first, faces[closest_face][3].first);
    colInfo.HasCollision = true;

    return colInfo;
}

inline void Collision::ResolveCollision(Collider& colliderA, Collider& colliderB) {
    RigidBody* rbA = dynamic_cast<RigidBody*>(colliderA.GetParentObject()->GetModuleByName("RigidBody"));  
    RigidBody* rbB = dynamic_cast<RigidBody*>(colliderB.GetParentObject()->GetModuleByName("RigidBody"));

    Simplex simplex;   
    if (!Collision::GJK(colliderA, colliderB, simplex)) { return; };
    CollisionInfo colInfo = Collision::EPA(simplex, colliderA, colliderB, rbA->_movementVector);

    if (rbA != nullptr && rbB == nullptr) {
        colliderA.GetParentObject()->AddPosition(-colInfo.Normal * colInfo.PenetrationDepth);
        colliderA.GetParentObject()->ApplyTransform();

        Physics::Contact(*rbA, -colInfo.Normal);      
    }
    else if (rbA == nullptr && rbB != nullptr) {
        colliderB.GetParentObject()->AddPosition(-colInfo.Normal * colInfo.PenetrationDepth);
        colliderB.GetParentObject()->ApplyTransform();

        Physics::Contact(*rbB, -colInfo.Normal);
    }
    else if (rbA != nullptr && rbB != nullptr) {

        Vector3 vec = Vector3::GetNormalize(-rbA->_movementVector) * (colInfo.PenetrationDepth + 0.002f);
        vec.X = round(vec.X * 100) / 100;
        Vector3 vec2 = -colInfo.Normal * (colInfo.PenetrationDepth + 0.002f);

        colliderA.GetParentObject()->AddPosition(-colInfo.Normal * (colInfo.PenetrationDepth - 0.002f));
        std::cout << colInfo.PenetrationDepth << std::endl;
        rbA->_movementVector = { 0,0,0 };
        //std::cout << vec.X << " " << vec.Y << " " << vec.Z << " " << std::endl;
        //std::cout << vec2.X << " " << vec2.Y << " " << vec2.Z << " " << std::endl;
        //Physics::Contact(*rbA, *rbB, -pushOutVector);
        //Physics::Contact(*rbA, *rbB, -rbA->_movementVector);
    }
}
