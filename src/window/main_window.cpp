// SPDX-License-Identifier: MIT
#include "main_window.hpp"

#include "../utils/logger.hpp"

static const int SCREEN_W = 800;
static const int SCREEN_H = 600;

namespace window {

MainWindow::MainWindow() {
    // TODO: Use exceptions instead of only logging errors

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // TODO: Log correctly
        LOG_ERROR("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    mp_window =
        SDL_CreateWindow("Fishing Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
    if (mp_window == nullptr) {
        LOG_ERROR("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    mp_screen_surface = SDL_GetWindowSurface(mp_window);
}

MainWindow::~MainWindow() {
    m_scene.clear();

    // Destroy window
    SDL_DestroyWindow(mp_window);
    mp_window = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

void MainWindow::draw() {
    SDL_FillRect(mp_screen_surface, NULL, SDL_MapRGB(mp_screen_surface->format, 0x00, 0x00, 0x00));
    m_scene->draw(mp_screen_surface);
    SDL_UpdateWindowSurface(mp_window);
}
} // namespace window