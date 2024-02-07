//
// Created by zhang on 2023/12/13.
//
#include"View/Renderer.h"

Renderer::Renderer(const Window&window) {
    renderer_ = SDL_CreateRenderer(window.window_, -1, 0);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer_);
    for (auto&it: BrightNumber) {
        if (it != nullptr)
            SDL_DestroyTexture(it);
    }
    for (auto&it: Greynumber) {
        if (it != nullptr) {
            SDL_DestroyTexture(it);
        }
    }
    SDL_DestroyTexture(PTexture);
}

void Renderer::SetColor(const SDL_Color&c) const {
    SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
}

void Renderer::Clear() const {
    SDL_RenderClear(renderer_);
}

void Renderer::Present() const {
    SDL_RenderPresent(renderer_);
}

void Renderer::DrawCircle(int centerX, int centerY, int radius) const {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer_, centerX + x, centerY + y);
            }
        }
    }
}

void Renderer::DrawRect(const SDL_Rect&rect) {
    SDL_RenderDrawRect(renderer_, &rect);
}

void Renderer::FillRect(const SDL_Rect&rect) {
    SDL_RenderFillRect(renderer_, &rect);
}

void Renderer::DrawLine(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer_, x1, y1, x2, y2);
}

void Renderer::drawNode(int x, int y, const std::string&s, TTF_Font* font, bool bright, bool mark) {
    const int num = stoi(s);

    if (BrightNumber[num] == nullptr) {
        const unsigned char r = num % 3 == 0 ? (num % 25) * 10 : 0;
        const unsigned char g = num % 3 == 1 ? (num % 25) * 5 : 0;
        const unsigned char b = num % 3 == 2 ? (num % 25) * 10 : 0;
        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, s.c_str(), SDL_Color{r, g, b, 200});
        BrightNumber[num] = SDL_CreateTextureFromSurface(renderer_, surface);
        SDL_FreeSurface(surface);
    }
    if (Greynumber[num] == nullptr) {
        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, s.c_str(), SDL_Color{100, 100, 100, 200});
        Greynumber[num] = SDL_CreateTextureFromSurface(renderer_, surface);
        SDL_FreeSurface(surface);
    }

    const int width = 10 * static_cast<int>(s.length());
    constexpr int height = 20;
    const SDL_Rect nodeRect = {x - width / 2, y - height / 2, width, height};
    if (bright)
        SDL_RenderCopy(renderer_, BrightNumber[num], nullptr, &nodeRect);
    else
        SDL_RenderCopy(renderer_, Greynumber[num], nullptr, &nodeRect);
    if (mark) {
        if (bright) {
            const unsigned char r = num % 3 == 0 ? (num % 25) * 10 : 0;
            const unsigned char g = num % 3 == 1 ? (num % 25) * 10 : 0;
            const unsigned char b = num % 3 == 2 ? (num % 25) * 10 : 0;
            SetColor(SDL_Color{r, g, b, 200});
        }
        else {
            SetColor(SDL_Color{100, 100, 100, 200});
        }
        // DrawRect(nodeRect);
        DrawLine(x - width / 2, y + height / 2, x + width / 2, y + height / 2);
    }
}

void Renderer::hightNode(int x, int y, const std::string&s, TTF_Font* font) {
    const int num = stoi(s);

    const unsigned char r = num % 3 == 0 ? (num % 25) * 10 : 0;
    const unsigned char g = num % 3 == 1 ? (num % 25) * 10 : 0;
    const unsigned char b = num % 3 == 2 ? (num % 25) * 10 : 0;
    if (BrightNumber[num] == nullptr) {
        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, s.c_str(), SDL_Color{r, g, b, 200});
        BrightNumber[num] = SDL_CreateTextureFromSurface(renderer_, surface);
        SDL_FreeSurface(surface);
    }

    const int width = 10 * static_cast<int>(s.length());
    constexpr int height = 20;
    const SDL_Rect nodeRect = {x - width / 2, y - height / 2, width, height};
    SDL_RenderCopy(renderer_, BrightNumber[num], nullptr, &nodeRect);
    SetColor(SDL_Color{r, g, b, 200});
    DrawRect(nodeRect);
}

void Renderer::drawP(int x, int y, TTF_Font* font) {
    if(PTexture==nullptr){
        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, s.c_str(), SDL_Color{0, 0, 0, 0});
        PTexture= SDL_CreateTextureFromSurface(renderer_, surface);
        SDL_FreeSurface(surface);
    }
    const int width = 10 * static_cast<int>(s.length());
    constexpr int height = 20;
    const SDL_Rect nodeRect = {x - width / 2, y - height / 2, width, height};
    SDL_RenderCopy(renderer_,PTexture,nullptr,&nodeRect);

}
