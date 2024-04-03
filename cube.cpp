#include "Structs.h" 
#include "cube.h"
#include "Renderer3D.h"
#include <iostream>
#include <vector>
#include <SDL.h>
#include <cmath>

using namespace std;

// Define points and edges for the cube
std::vector<Point3D> points{
    Point3D{0, -2, 0}, Point3D{1, -1, -1},
    Point3D{-1, -1, -1}, Point3D{1, -1, 1},
    Point3D{-1, -1, 1},
};

std::vector<Edge> edges{
    Edge{0, 1},
    Edge{0, 2},
    Edge{0, 3},
    Edge{0, 4},
    Edge{1, 2},
    Edge{2, 4},
    Edge{4, 3},
    Edge{3, 1},
};

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    window = SDL_CreateWindow("Pulsating Cube Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    Renderer3D render3D(window, renderer, points, edges);

    // Main loop
    while (running) {
        // Handle events
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        // Calculate pulsating scale
        float scale = 0.5f + 0.5f * sin(SDL_GetTicks() / 500.0); // Adjust the pulsating scale

        // Apply pulsating effect to points
        for (Point3D& point : points) {
            point.x *= scale;
            point.y *= scale;
            point.z *= scale;
        }

        // Render
        SDL_SetRenderDrawColor(renderer, 128, 0, 128, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        render3D.render();
        SDL_RenderPresent(renderer);

        // Delay
        SDL_Delay(20);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
