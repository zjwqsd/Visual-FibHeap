//
// Created by zhang on 2023/12/13.
//
#include"view/window.h"
Window::Window(const std::string&title, int w, int h) {
    window_ = SDL_CreateWindow("Visual-Tree",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        w,h,SDL_WINDOW_SHOWN);
}
Window::~Window() {
    SDL_DestroyWindow(window_);
}
