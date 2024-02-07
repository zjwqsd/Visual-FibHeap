//
// Created by zhang on 2023/12/13.
//
#include"View/Context.h"
std::unique_ptr<Context>Context::instance_ = nullptr;
TTF_Font* Context::font=nullptr;
void Context::Init() {
    if(!instance_) {
        TTF_Init();
        Window window("Visual-Tree",1500,600);
        Renderer renderer(window);
        instance_= std::make_unique<Context>(Context{
            std::move(window),std::move(renderer)
        });
        font = TTF_OpenFont("font.ttf",50);
        if (font==nullptr) {
            SDL_Log("sdl init failed");
        }
    }
}

void Context::Quit() {
    TTF_CloseFont(font);
    TTF_Quit();
    instance_.reset();
}

Context& Context::Inst() {
    SDL_assert(instance_);
    return (*instance_);
}

void Context::drawNode(const std::vector<View::Multi_node>& arr, int id,bool bright) {

    const View::Multi_node &cur = arr[id];
    renderer.drawNode(cur.x,cur.y,cur.text,font,bright,cur.mark);
    renderer.SetColor(SDL_Color{100,100,100,100});
    if(cur.father_id!=-1) {
        const View::Multi_node &father = arr[cur.father_id];
        renderer.DrawLine(cur.x,cur.y,father.x,father.y);
    }
}
void Context::drawTree(const std::vector<View::Multi_node>& arr,bool bright) {
    for(int i=0;i<arr.size();i++) {
        if(arr[i].exist)
            drawNode(arr,i,bright);
    }
}
