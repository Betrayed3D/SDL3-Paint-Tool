#include<iostream>
#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>

int main(int argc, char* argv[])
{
    // Start SDL subsystems
    if(SDL_Init(SDL_INIT_VIDEO) == false)
    {
        SDL_Log("SDL failed to start! Error: ", SDL_GetError());
        return -1;
    }

    // Create the main window
    constexpr int WindowWidth{1000};
    constexpr int WindowHeight{800};
    SDL_Window* MainWindow{SDL_CreateWindow("Paint Tool!", WindowWidth, WindowHeight, SDL_WINDOW_RESIZABLE)};
    if(MainWindow == NULL)
    {
        SDL_Log("SDL failed to create window! Error: ", SDL_GetError());
        SDL_DestroyWindow(MainWindow);
        SDL_Quit();
        return -1;
    }

    // Create the renderer
    SDL_Renderer* MainRenderer{SDL_CreateRenderer(MainWindow, NULL)};
    if(MainRenderer == NULL)
    {
        SDL_Log("SDL failed to create renderer! Error: ", SDL_GetError());
        SDL_DestroyWindow(MainWindow);
        SDL_DestroyRenderer(MainRenderer);
        SDL_Quit();
        return -1;
    }
    else
    {
        SDL_SetRenderLogicalPresentation(MainRenderer, WindowWidth, WindowHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);        
    }

    // Program Loop
    bool AppRunning{true};
    while(AppRunning == true)
    {
        // Handle events
        SDL_Event Event;
        while(SDL_PollEvent(&Event) == true)
        {
            switch (Event.type)
            {
            case SDL_EVENT_QUIT:
                SDL_DestroyWindow(MainWindow);
                SDL_DestroyRenderer(MainRenderer);
                SDL_Quit();
                AppRunning = false;
                break;
            default:
                break;
            }
        }
        // Everything else
        const double TimeNow{(double(SDL_GetTicks()) / 1000.0)};
        const float red{(float) (0.5 + 0.5 * SDL_sin(TimeNow))};
        const float green{(float) (0.5 + 0.5 * SDL_sin(TimeNow + SDL_PI_D * 2 / 3))};
        const float blue{(float) (0.5 + 0.5 * SDL_sin(TimeNow + SDL_PI_D * 4 / 3))};
        SDL_SetRenderDrawColorFloat(MainRenderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);

        SDL_RenderClear(MainRenderer);
        SDL_RenderPresent(MainRenderer);
    }

    return 0;
}