#include "cubeNoOOP.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <SDL.h>

struct Point2D { float x; float y; };
struct Point3D { float x; float y; float z; };
struct Edge { int start; int end; };

int WindowSizeX;
int WindowSizeY;
SDL_Renderer* renderer;
float DeltaTime = 0;
float FL = 5;


//Creates an array of points
std::vector<Point3D> points2{
         Point3D{ -1, -1, -1 }, Point3D{ -1, -1, 1 },
         Point3D{ 1,  -1, -1 }, Point3D{ -1,  1, -1 },
         Point3D{ -1, 1, 1 }, Point3D{ 1,  -1, 1 },
         Point3D{ 1,  1, -1 }, Point3D{ 1,  1, 1 }
};

//creates an array of edges (This hold indices referencing to the points array)
std::vector<Edge> edges2{
         Edge{ 0, 1 },
         Edge{ 0, 2 },
         Edge{ 0, 3 },
         Edge{ 2, 5 },
         Edge{ 3, 6 },
         Edge{ 3, 4 },
         Edge{ 4, 7 },
         Edge{ 6, 7 },
         Edge{ 7, 5 },
         Edge{ 5, 1 },
         Edge{ 4, 1 },
         Edge{ 2, 6 },
};

Point2D projection2(Point3D point)
{
    return Point2D{ WindowSizeX / 2 + (point.x * FL) / (FL + point.z) * 100, WindowSizeY / 2 + (point.y * FL) / (FL + point.z) * 100 };
}

void render2(std::vector<Point3D> points, std::vector<Edge> edges)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    //rotation += 1 * DeltaTime;

    for (auto& edge : edges) {
        Point2D start = projection2(points[edge.start]);
        Point2D end = projection2(points[edge.end]);

        SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
    }

    SDL_RenderPresent(renderer);
}

//Main functions are the start point of this C++ solution so the solution will not run if two main functions are
//in a single solution. To run this file, comment or delete (at your own peril) the main file in the cube.cpp file
//and remove the comments from the main file below
/*

//default C++ function
int main(int argc, char* argv[])
{
    //creating a window and a renderer
    SDL_Window* window;

    //creates a centered window with 960 width and 540 height
    window = SDL_CreateWindow("Cube Renderer No OOP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_GetWindowSize(window, &WindowSizeX, &WindowSizeY);

    bool running = true;

    while (running)
    {
        //if the quit button is pressed, the loop breaks
        if (SDL_QuitRequested()) { running = false; break; }

        //Calls the function created in the Renderer3D class (render 3D is an instance of the class defined above)
        render2(points2, edges2);
    }

    return 0;
}

*/

//This file encapsulates all the code we did in the other three files here. As I became aware the issue
//was C++ structure and OOP. The same thing done in the previous three files in put here. 
//This is however not the best method to use to code as once you begin to extend, your codebase becomes
//harder to work with. 
