//
// Created by zhang on 2023/12/13.
//

#ifndef CONTSXT_H
#define CONTSXT_H
#include"window.h"
#include"Renderer.h"
#include "SDL2/SDL_ttf.h"


struct Context final {

    Window window;

    Renderer renderer;

    static TTF_Font* font;

    Context(Window&&window, Renderer&&renderer): window(std::move(window)), renderer(std::move(renderer)) {
    }

    void Clear() const {
        renderer.SetColor(SDL_Color{200, 200, 200, 255});
        renderer.Clear();
    }

    static void Init();

    static void Quit();

    static Context& Inst();

    void drawNode(const std::vector<View::Multi_node>&arr, int id, bool bright);
    void highlightNode(const std::vector<View::Multi_node>&arr, int id) {
        renderer.hightNode(arr[id].x,arr[id].y,arr[id].text,font);
    }

    void drawTree(const std::vector<View::Multi_node>&arr, bool bright);


    void drawInput(const std::string&s, int x, int y) {
        renderer.drawNode(x, y, s, font, true, false);
    }
    void drawNULL(int x,int y) {
        renderer.SetColor(SDL_Color{0,0,0,0});
        renderer.FillRect(SDL_Rect{x-5,y-5,10,10});
    }
    void drawP(int p) {
        //renderer.SetColor(SDL_Color{50,50,50,50});
        renderer.drawP(650,550,font);
        renderer.drawNode(750,550,std::to_string(p),font,true,false);

    }
private:
    static std::unique_ptr<Context> instance_;
};
#endif //CONTSXT_H
