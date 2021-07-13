#include <SDL.h>
#include <iostream>

// Starts up SDL and creates window
bool init();

// Loads media
bool load_media();

// Frees media and shuts down SDL
void close_sdl();

// Rendered window
SDL_Window* g_window = nullptr;

// The surfae contained by the window
SDL_Surface* g_screen_surface = nullptr;

// The image we will load and show on the screen
SDL_Surface* g_hello_world = nullptr;

// Define width and height of window
constexpr int g_screen_width  = 600;
constexpr int g_screen_height = 460;

bool init()
{
    // INitialization flag
    bool success = true;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not inizailize! SDL_Error; $s\n"
                  << SDL_GetError() << std::endl;
        success = false;
    }
    else {
        // Create window
        g_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, g_screen_width, g_screen_height, SDL_WINDOW_SHOWN);
        if(g_window == nullptr) {
            std::cout << "Window could not be reated! SDL_Error: %s\n"
                      << SDL_GetError() << std::endl;
            success = false;
        }
        else {
            // Get window surface
            g_screen_surface = SDL_GetWindowSurface(g_window);
        }
    }

    return success;
}

bool load_media()
{
    // Loading success flag
    bool success = true;

    // Load splash image
    g_hello_world = SDL_LoadBMP("../sdl_tutorial/images/hello_world.bmp");
    if(g_hello_world == nullptr) {
        char* base_path = SDL_GetBasePath();
        std::cout << base_path << std::endl
                  << "Unable to load image %s! SDL Error: %s\n"
                  << "src/hello_world.bmp" << SDL_GetError() << std::endl;
        success = false;
    }
    return success;
}

void close()
{
    // Deallocate surface
    SDL_FreeSurface(g_hello_world);
    g_hello_world = nullptr;

    // Destroy window
    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char* args[])
{
    // Start up SDL and  create window
    if(!init()) {
        std::cout << "Failed to initialize!\n"
                  << std::endl;
    }
    else {
        // Load media
        if(!load_media()) {
            std::cout << "Failed to load media!" << std::endl;
        }
        else {
            // Apply the image
            SDL_BlitSurface(g_hello_world, nullptr, g_screen_surface, nullptr);
            // Update the surface
            SDL_UpdateWindowSurface(g_window);
            SDL_Delay(2000);
        }
    }

    bool quit = false;

    // Event handler
    SDL_Event e;

    while(!quit) {
        // Handle events on queue
        while(SDL_PollEvent(&e) != 0) {
            // User requests quit
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        // Apply the image
        SDL_BlitSurface(g_hello_world, nullptr, g_screen_surface, nullptr);

        // Update the surface
        SDL_UpdateWindowSurface(g_window);
    }

    // Free resources and close SDL
    close();
    return 0;
}
