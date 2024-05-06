#include "test.h"
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int IMAGE_WIDTH = SCREEN_WIDTH - 300;
const int IMAGE_PADDING = 100; // Space between images and window boundary

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int speed = 0.1;
int CameraX = 0;
int textureWidthDiff = IMAGE_WIDTH - SCREEN_WIDTH;

SDL_Texture* loadTexture(const std::string& path) {
    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

bool initSDL()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create window
    gWindow = SDL_CreateWindow("2D Rendering", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Set renderer color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Allows for (Initializes) Image Loading abilities using SDL_image library
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

void closeSDL()
{
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!initSDL()) {
        printf("Failed to initialize SDL!\n");
        return -1;
    }

    // Load the first image
    SDL_Texture* image1 = loadTexture("C:/Users/anuol/Downloads/SDL_BaseProject/SDL_BaseProject/Assets/Tree.jpg");
    if (image1 == NULL) {
        printf("Failed to load image1!\n");
        closeSDL();
        return -1;
    }

    // Load the second image
    SDL_Texture* image2 = loadTexture("C:/Users/anuol/Downloads/SDL_BaseProject/SDL_BaseProject/Assets/ball.png");
    if (image2 == NULL) {
        printf("Failed to load image2!\n");
        SDL_DestroyTexture(image1);
        closeSDL();
        return -1;
    }

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear screen
        SDL_RenderClear(gRenderer);

        // Render image1 in the top half of the window
        SDL_Rect image1Dest = { IMAGE_PADDING, IMAGE_PADDING, SCREEN_WIDTH - 2 * IMAGE_PADDING, (SCREEN_HEIGHT - 3 * IMAGE_PADDING) / 2 };
        SDL_RenderCopy(gRenderer, image1, NULL, &image1Dest);

        // Render image2 in the bottom half of the window
        SDL_Rect image2Dest = { IMAGE_PADDING, (SCREEN_HEIGHT + IMAGE_PADDING) / 2, SCREEN_WIDTH - 2 * IMAGE_PADDING, (SCREEN_HEIGHT - 3 * IMAGE_PADDING) / 2 };
        SDL_RenderCopy(gRenderer, image2, NULL, &image2Dest);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }

    // Destroy textures
    SDL_DestroyTexture(image1);
    SDL_DestroyTexture(image2);

    // Close SDL
    closeSDL();

    return 0;
}
