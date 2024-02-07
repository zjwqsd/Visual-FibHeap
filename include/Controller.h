//
// Created by zhang on 2023/12/13.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "View/Context.h"
#include "Model/Model.h"


class Controller {
    Model model_;

    enum {
        build,
        insert,
        search
    } mode;

    SDL_Event event{};
    bool isquit = false;

    int interval = 10;
    int MouseX, MouseY;

public:
    void run();

private:
    void MessageHandling();

    void InsertMode();

    void SearchMode();

    void BuildMode();

public:
    Controller();

    ~Controller() {
        Context::Quit();
    }

private:
    //功能函数

    Multi_node* target = nullptr;


    void highlight(Multi_node* target);


    void showFibHeap(HeapID id, int rootX, int rootY, bool ismove, bool bright, int interval);

private:
    void drawInput() const;
    void drawPotential();
    void input(char x);

    std::string Input;
};


#endif //CONTROLLER_H
