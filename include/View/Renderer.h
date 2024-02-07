//
// Created by zhang on 2023/12/13.
//

#ifndef RENDERER_H
#define RENDERER_H

#include"pch.h"
#include "window.h"
#include<SDL2/SDL_ttf.h>
inline std::vector<SDL_Texture *> BrightNumber(10000, nullptr);
inline std::vector<SDL_Texture *> Greynumber(10000, nullptr);
inline SDL_Texture* PTexture=nullptr;
class Renderer final {
    //std::vector<SDL_Texture*>numberTexture;
public:
    explicit Renderer(const Window&);

    Renderer(const Renderer&) = delete;

    Renderer(Renderer&&other) noexcept {
        renderer_ = other.renderer_;
        other.renderer_ = nullptr;
    }

    Renderer& operator=(const Renderer&) = delete;

    ~Renderer();

    void SetColor(const SDL_Color&) const;

    void Clear() const;

    void Present() const;

public: //基本绘图
    void DrawCircle(int centerX, int centerY, int radius) const;

    void DrawRect(const SDL_Rect&rect);
    void FillRect(const SDL_Rect&rect);

    void DrawLine(int x1, int y1, int x2, int y2);


    void drawNode(int x, int y, const std::string&s, TTF_Font* font, bool bright, bool mark);
    void hightNode(int x,int y,const std::string&s,TTF_Font*font);
    void drawP(int x, int y,  TTF_Font* font);
private:
    const std::string s = "The potential is";
    //SDL_Texture* pTexture;
    SDL_Renderer* renderer_;
};
#endif //RENDERER_H
