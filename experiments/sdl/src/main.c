#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Start SDL and create window
bool init(void);

// Load media
bool loadMedia(void);

// Free media and shut down SDL
void close(void);

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// The image we will load and show on the screen
SDL_Surface *gSpriteSheetSurface = NULL;

// Current displayed sprite
SDL_Surface *gCurrentClip = NULL;

bool init(void) {
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Get window surface
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

bool loadMedia(void) {
  // Loading success flag
  bool success = true;

  // Load sprite sheet
  gSpriteSheetSurface = IMG_Load("./assets/dino_sprites_mort.png");
  if (gSpriteSheetSurface == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n",
           "./dino_sprites_mort.png", SDL_GetError());
    success = false;
  }

  return success;
}

void close(void) {
  // Deallocate surface
  SDL_FreeSurface(gSpriteSheetSurface);
  gSpriteSheetSurface = NULL;

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}

int main(void) {
  if (!init())
    printf("Failed to initialize!\n");
  else {
    if (!loadMedia()) {
      printf("Failed to load media!\n");
    } else {
      // Load media
      if (!loadMedia())
        printf("Failed to load media!\n");
      else {
        // Main loop flag
        bool quit = false;

        // Event handler
        SDL_Event e;

        // Animation frame
        int frame = 0;
        int totalFrames = 15;
        int spriteWidth = 24;
        int spriteHeight = 24;

        // Initialize gCurrentClip
        SDL_Rect gCurrentClip = {0, 0, spriteWidth, spriteHeight};

        // Desired frame rate
        const int FPS = 30;
        const int frameDelay = 1000 / FPS;

        // While application is running
        while (!quit) {
          // Handle events on queue
          while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT)
              quit = true;
          }
          // clear the screen
          SDL_FillRect(gScreenSurface, NULL, 0x000000);

          // Calculate the frame to show

          gCurrentClip.x = spriteWidth * (frame % totalFrames);

          // Render the current frame
          SDL_BlitSurface(gSpriteSheetSurface, &gCurrentClip, gScreenSurface,
                          NULL);

          // Update the surface
          SDL_UpdateWindowSurface(gWindow);

          // Go to next frame
          ++frame;
          if (frame >= totalFrames) {
            frame = 0;
          }
          // Wait 2 seconds per frame
          SDL_Delay(frameDelay);
        }
      }
      close();
    }
    return 0;
  }
}
