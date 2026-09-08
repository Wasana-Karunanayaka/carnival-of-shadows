#pragma once
/*
 * File: HauntedTree.h
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Draws reusable procedural dead trees using recursive branches.
 */

#pragma once

class HauntedTree
{
public:
    static void draw(float variation = 0.0f);

private:
    static void drawBranch(int depth, float length, float radius, float variation);
    static void drawRoots(float variation);
};