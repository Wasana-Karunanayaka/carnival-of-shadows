/*
 * File: Mesh.h
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Defines reusable data structures for representing 3D geometry.
 *
 * This file contains no OpenGL drawing code. It only stores the
 * mathematical description of a mesh: vertices, edges, faces and normals.
 */

#pragma once

#include <vector>

 /*
  * Represents one point in 3D space.
  */
struct Vertex
{
    float x;
    float y;
    float z;
};

/*
 * Represents a connection between two vertices.
 *
 * The integers refer to positions inside Mesh::vertices.
 */
struct Edge
{
    int startIndex;
    int endIndex;
};

/*
 * Represents one polygonal surface of a mesh.
 *
 * vertexIndices stores the vertices that form the face.
 */
struct Face
{
    std::vector<int> vertexIndices;
};

/*
 * Represents the direction perpendicular to a surface.
 *
 * Normals are later used by OpenGL lighting calculations.
 */
struct Normal
{
    float x;
    float y;
    float z;
};


/*
 * Stores the geometric data of a reusable 3D object.
 *
 * Mesh does not know anything about windows, cameras,
 * keyboard input or OpenGL rendering.
 */
class Mesh
{
public:

    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    std::vector<Face> faces;

    // One normal is currently stored for each face.
    std::vector<Normal> normals;


    /*
     * Adds a vertex to the mesh.
     */
    void addVertex(float x, float y, float z);


    /*
     * Adds an edge connecting two existing vertices.
     */
    void addEdge(int startIndex, int endIndex);


    /*
     * Adds a polygonal face using vertex indices.
     */
    void addFace(const std::vector<int>& indices);


    /*
     * Calculates a normalized surface normal for every face.
     *
     * The normal is calculated using the cross product of
     * two vectors lying on the face.
     */
    void computeNormals();


    /*
     * Creates a cube centered at the origin.
     *
     * Parameters:
     *     size - Total width, height and depth.
     *
     * Returns:
     *     A completed cube Mesh.
     */
    static Mesh createCube(float size);
};