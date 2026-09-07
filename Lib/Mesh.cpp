/*
 * File: Mesh.cpp
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Implements mesh construction and geometry calculations.
 */

#include "pch.h"
#include "Mesh.h"

#include <cmath>


void Mesh::addVertex(float x, float y, float z)
{
    vertices.push_back({ x, y, z });
}


void Mesh::addEdge(int startIndex, int endIndex)
{
    edges.push_back({ startIndex, endIndex });
}


void Mesh::addFace(const std::vector<int>& indices)
{
    faces.push_back({ indices });
}


/*
 * Calculates one normal for each face using the cross product.
 */
void Mesh::computeNormals()
{
    normals.clear();

    for (const Face& face : faces)
    {
        // At least three vertices are required to define a surface.
        if (face.vertexIndices.size() < 3)
        {
            normals.push_back({ 0.0f, 0.0f, 0.0f });
            continue;
        }

        const Vertex& v0 = vertices[face.vertexIndices[0]];
        const Vertex& v1 = vertices[face.vertexIndices[1]];
        const Vertex& v2 = vertices[face.vertexIndices[2]];

        // Construct two vectors lying on the face.
        float ux = v1.x - v0.x;
        float uy = v1.y - v0.y;
        float uz = v1.z - v0.z;

        float vx = v2.x - v0.x;
        float vy = v2.y - v0.y;
        float vz = v2.z - v0.z;

        // Cross product u x v gives a vector perpendicular to the face.
        Normal normal;

        normal.x = (uy * vz) - (uz * vy);
        normal.y = (uz * vx) - (ux * vz);
        normal.z = (ux * vy) - (uy * vx);

        float length = std::sqrt(
            normal.x * normal.x +
            normal.y * normal.y +
            normal.z * normal.z
        );

        // Convert the normal to unit length.
        if (length > 0.0f)
        {
            normal.x /= length;
            normal.y /= length;
            normal.z /= length;
        }

        normals.push_back(normal);
    }
}


/*
 * Builds a cube from eight shared vertices.
 */
Mesh Mesh::createCube(float size)
{
    Mesh mesh;

    // Keeping coordinates at +/- halfSize centers the cube at (0, 0, 0).
    float halfSize = size / 2.0f;


    // --------------------
    // Vertices
    // --------------------

    mesh.addVertex(-halfSize, -halfSize, -halfSize); // 0
    mesh.addVertex(halfSize, -halfSize, -halfSize); // 1
    mesh.addVertex(halfSize, halfSize, -halfSize); // 2
    mesh.addVertex(-halfSize, halfSize, -halfSize); // 3

    mesh.addVertex(-halfSize, -halfSize, halfSize); // 4
    mesh.addVertex(halfSize, -halfSize, halfSize); // 5
    mesh.addVertex(halfSize, halfSize, halfSize); // 6
    mesh.addVertex(-halfSize, halfSize, halfSize); // 7


    // --------------------
    // Edges
    // --------------------

    // Back square
    mesh.addEdge(0, 1);
    mesh.addEdge(1, 2);
    mesh.addEdge(2, 3);
    mesh.addEdge(3, 0);

    // Front square
    mesh.addEdge(4, 5);
    mesh.addEdge(5, 6);
    mesh.addEdge(6, 7);
    mesh.addEdge(7, 4);

    // Connections between front and back
    mesh.addEdge(0, 4);
    mesh.addEdge(1, 5);
    mesh.addEdge(2, 6);
    mesh.addEdge(3, 7);


    // --------------------
    // Faces
    // --------------------
    //
    // Vertex order is chosen so the face normals point outward.

    mesh.addFace({ 0, 3, 2, 1 }); // Back
    mesh.addFace({ 4, 5, 6, 7 }); // Front

    mesh.addFace({ 0, 1, 5, 4 }); // Bottom
    mesh.addFace({ 3, 7, 6, 2 }); // Top

    mesh.addFace({ 1, 2, 6, 5 }); // Right
    mesh.addFace({ 0, 4, 7, 3 }); // Left


    // Normals are needed when lighting is enabled.
    mesh.computeNormals();

    return mesh;
}