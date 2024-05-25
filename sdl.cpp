//#include "sdl.h"
//#include <SDL.h>
//#include <stdio.h>
//#include <SDL_image.h>
//#include <string>
//#include <vector>
//
//const int SCREEN_WIDTH = 800;
//const int SCREEN_HEIGHT = 600;
//const int IMAGE_WIDTH = SCREEN_WIDTH + 300;
//
//SDL_Window* gWindow = NULL;
//SDL_Renderer* gRenderer = NULL;
//float speed = 0.1;
//int CameraX = 0;
//int textureWidthDiff = IMAGE_WIDTH - SCREEN_WIDTH;
//
//SDL_Texture* loadTexture(const std::string& path) {
//    // The final texture
//    SDL_Texture* newTexture = NULL;
//
//    // Load image at specified path
//    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//    if (loadedSurface == NULL) {
//        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
//    }
//    else {
//        // Create texture from surface pixels
//        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
//        if (newTexture == NULL) {
//            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//        }
//
//        // Get rid of old loaded surface
//        SDL_FreeSurface(loadedSurface);
//    }
//
//    return newTexture;
//}
//
//bool initSDL()
//{
//    // Initialize SDL
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//        return false;
//    }
//
//    // Create window
//    gWindow = SDL_CreateWindow("2D Rendering", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//    if (gWindow == NULL) {
//        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
//        return false;
//    }
//
//    // Create renderer
//    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    if (gRenderer == NULL) {
//        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
//        return false;
//    }
//
//    // Set renderer color
//    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//
//    // Allows for (Initializes) Image Loading abilities using SDL_image library
//    int imgFlags = IMG_INIT_PNG;
//    if (!(IMG_Init(imgFlags) & imgFlags)) {
//        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
//        return false;
//    }
//
//    return true;
//}
//
//void closeSDL()
//{
//    // Destroy window
//    SDL_DestroyRenderer(gRenderer);
//    SDL_DestroyWindow(gWindow);
//    gWindow = NULL;
//    gRenderer = NULL;
//
//    // Quit SDL subsystems
//    IMG_Quit();
//    SDL_Quit();
//}
//
//int main(int argc, char* argv[]) {
//    if (!initSDL()) {
//        printf("Failed to initialize SDL!\n");
//        return -1;
//    }
//
//    std::vector<SDL_Texture*> backgroundTextures;
//    backgroundTextures.push_back(loadTexture("./assets/pic/wool.png"));
//
//    SDL_Texture* backgroundFloor = loadTexture("./assets/pic/velvet.png");
//    SDL_Texture* backgroundSky = loadTexture("./assets/pic/lay.png");
//
//    // Main loop flag
//    bool quit = false;
//
//    // Event handler
//    SDL_Event e;
//
//    while (!quit) {
//        // Handle events on queue
//        while (SDL_PollEvent(&e) != 0) {
//            // User requests quit
//            if (e.type == SDL_QUIT) {
//                quit = true;
//            }
//        }
//
//        // Clear screen
//        SDL_RenderClear(gRenderer);
//
//        // Render backgroundFloor if you want to show it
//        
//
//        int offsetX = CameraX * speed;  // Calculate offset based on camera position
//        for (SDL_Texture* texture : backgroundTextures) {
//            SDL_Rect textureDest = { offsetX, 200, IMAGE_WIDTH, SCREEN_HEIGHT };
//            SDL_RenderCopy(gRenderer, texture, NULL, &textureDest);
//        }
//
//        // Render backgroundSky if you want to show it
//        SDL_Rect skyDest = { 200, 200, 400, 300 };
//        SDL_RenderCopy(gRenderer, backgroundSky, NULL, &skyDest);
//
//        // Update screen
//        SDL_RenderPresent(gRenderer);
//    }
//
//    // Destroy textures
//    SDL_DestroyTexture(backgroundFloor);
//    SDL_DestroyTexture(backgroundSky);
//
//    for (SDL_Texture* texture : backgroundTextures) {
//        SDL_DestroyTexture(texture);
//    }
//
//    // Close SDL
//    closeSDL();
//
//    return 0;
//}


#include "test.h"
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <vector>


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int IMAGE_WIDTH = SCREEN_WIDTH + 300;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int speed = 0.1;
int CameraX = 0;
int textureWidthDiff = IMAGE_WIDTH - SCREEN_WIDTH;


int x = SCREEN_WIDTH / 2;
int y = SCREEN_HEIGHT / 2;

const int BALL_RADIUS = 72;
int dx = 5;
int dy = 5;


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

void updateBall() {
	

	x += dx;
	y += dy;

	

	//printf("y Value is: %d\n",y);

	// Check collision with window edges
	if (x < 0 || x + BALL_RADIUS > SCREEN_WIDTH) {
		dx *= -1;
	}
	if (y < 0 || y + BALL_RADIUS > SCREEN_HEIGHT) {
		dy *= -1;
		printf("y Value is: \n", y);

		if (std::abs(dy) < 3) {
			y = SCREEN_HEIGHT - BALL_RADIUS;
		}
	}
}


int main(int argc, char* argv[]) {
	if (!initSDL()) {
		printf("Failed to initialize SDL!\n");
		return -1;
	}


	/*
	std::vector<SDL_Texture*> backgroundTextures;
	backgroundTextures.push_back(loadTexture("./Assets/Pixel_Forest/layer0.png"));
	backgroundTextures.push_back(loadTexture("./Assets/Pixel_Forest/layer1.png"));
	backgroundTextures.push_back(loadTexture("./Assets/Pixel_Forest/layer2.png"));
	backgroundTextures.push_back(loadTexture("./Assets/Pixel_Forest/layer3.png"));
	backgroundTextures.push_back(loadTexture("./Assets/Pixel_Forest/layer4.png"));
	backgroundTextures.push_back(loadTexture("./Assets/Pixel_Forest/layer5.png"));
	backgroundTextures.push_back(loadTexture("./Assets/Pixel_Forest/layer6.png"));
	backgroundTextures.push_back(loadTexture("./Assets/Pixel_Forest/layer7.png"));
	backgroundTextures.push_back(loadTexture("./Assets/Pixel_Forest/layer8.png"));
	backgroundTextures.push_back(loadTexture("./Assets/Pixel_Forest/layer9.png"));
	backgroundTextures.push_back(loadTexture("./Assets/Pixel_Forest/layer10.png"));
	backgroundTextures.push_back(loadTexture("./Assets/Pixel_Forest/layer11.png"));
	*/

	SDL_Texture* ballText = loadTexture("./assets/ball.png");
	

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

		updateBall();

		SDL_Rect ballRect = {x, y, BALL_RADIUS, BALL_RADIUS };
		SDL_RenderCopy(gRenderer, ballText, NULL, &ballRect);

		//SDL_RenderCopy(gRenderer, backgroundFloor, NULL, NULL);

		/*
		for (SDL_Texture* texture : backgroundTextures) {
			SDL_Rect textureDest = { 0, 0, IMAGE_WIDTH, SCREEN_HEIGHT };
			SDL_RenderCopy(gRenderer, texture, NULL, &textureDest);
		}
		*/

		// Update screen
		SDL_RenderPresent(gRenderer);
		SDL_Delay(10);
	}

	// Destroy textures
	//SDL_DestroyTexture(enemyTexture);
	SDL_DestroyTexture(ballText);

	/*
	for (SDL_Texture* texture : backgroundTextures) {
		SDL_DestroyTexture(texture);
	}
	*/

	// Close SDL
	closeSDL();

	return 0;
}
