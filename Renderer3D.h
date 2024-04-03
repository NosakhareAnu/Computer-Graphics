#pragma once
#include <SDL.h>
#include <vector>
#include <chrono>
#include "Structs.h"  // Include the structs definition

class Renderer3D
{
public:
    Renderer3D(SDL_Window* _window, SDL_Renderer* renderer, std::vector<Point3D>& _points, std::vector<Edge>& _edges);
    void render();

private:
    Point2D projection(Point3D point);

    float FL = 5;

    float DeltaTime = 0;

    int WindowSizeX;
    int WindowSizeY;

    SDL_Renderer* SDL_render;

    std::vector<Point3D> points;
    std::vector<Edge> edges;
};
