//
// Created by zhang on 2023/12/13.
//

#ifndef WINDOW_H
#define WINDOW_H
#include"pch.h"



class Window final {
public:
    friend class Renderer;
    Window(const std::string& title,int w,int h);
    Window(const Window&)=delete;
    Window(Window&& other)  noexcept {
        window_ = other.window_;
        other.window_= nullptr;
    }
    Window& operator=(const Window&) = delete;
    ~Window();

private:
    SDL_Window* window_;
};




#endif //WINDOW_H
