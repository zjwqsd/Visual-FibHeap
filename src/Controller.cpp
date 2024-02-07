//
// Created by zhang on 2023/12/13.
//

#include "Controller.h"

#include <string>

Controller::Controller(): mode(insert) {
    SDL_Init(SDL_INIT_EVERYTHING);
    Context::Init();
    MouseX = 300;
    MouseY = 400;
    //InputBox = {300, 500, 30, 10};
}

void Controller::InsertMode() {
    const HeapID now = model_.get;
    int&rootx = model_.rootPosition[now].first;
    int&rooty = model_.rootPosition[now].second;
    switch (event.type) {
        case SDL_QUIT: isquit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            Context::Inst().Clear();
            if (event.button.button == SDL_BUTTON_LEFT) {
                MouseX = event.motion.x;
                MouseY = event.motion.y;
                showFibHeap(now, rootx, rooty, false, true, interval);

                drawInput();
            }
            else if (event.button.button == SDL_BUTTON_RIGHT) {
                //Context::Inst().Clear();
                const int val = model_.getVal(now, event.motion.x, event.motion.y);
                if (val == 10000) {
                    break;
                }
                model_.deleteFibNode(val);
                showFibHeap(now, rootx, rooty, true, true, interval);
                Input.clear();
                //showFibHeap(now, rootx, rooty, true, true, interval);
            }
            drawPotential();
            Context::Inst().renderer.Present();
            break;
        case SDL_KEYDOWN: {
            Context::Inst().Clear();
            bool ismove = false;
            switch (event.key.keysym.sym) {
                case SDLK_b:
                    mode = build;
                    model_.get = model_.other = -1;
                    break;
                case SDLK_s:
                    mode = search;
                    break;
                case SDLK_x:
                    interval++;
                    break;
                case SDLK_z:
                    if (interval > 0) {
                        interval--;
                    }
                    break;
                case SDLK_RIGHT:
                    rootx += 10;
                    ismove = true;
                    break;
                case SDLK_LEFT:
                    rootx -= 10;
                    ismove = true;
                    break;
                case SDLK_UP:
                    rooty -= 10;
                    ismove = true;
                    break;
                case SDLK_DOWN:
                    rooty += 10;
                    ismove = true;
                    break;
                case SDLK_r: {
                    model_.add_Heapnode(rand() % 9999);
                    ismove = true;
                    break;
                }
                case SDLK_e:
                    if (!model_.empty(now)) {
                        model_.ExtraMin();
                        ismove = true;
                    }
                    break;

                case SDLK_c:
                    model_.init_Fib();
                    ismove = true;
                    break;

                case SDLK_0:
                    if (!Input.empty())
                        input('0');
                    break;
                case SDLK_1:
                    input('1');
                    break;
                case SDLK_2:
                    input('2');
                    break;
                case SDLK_3:
                    input('3');
                    break;
                case SDLK_4:
                    input('4');
                    break;
                case SDLK_5:
                    input('5');
                    break;
                case SDLK_6:
                    input('6');
                    break;
                case SDLK_7:
                    input('7');
                    break;
                case SDLK_8:
                    input('8');
                    break;
                case SDLK_9:
                    input('9');
                    break;
                case SDLK_BACKSPACE:
                    if (!Input.empty()) {
                        Input.pop_back();
                        ismove = true;
                    }
                    break;
                case SDLK_RETURN:
                    if (Input.empty()) {
                        break;
                    }
                    ismove = true;
                    model_.add_Heapnode(stoi(Input));
                    Input.clear();
                    break;

                default: break;
            }
            showFibHeap(now, rootx, rooty, ismove, true, interval);

            drawInput();
            //drawPotential();
            Context::Inst().renderer.Present();
            break;
        }

        default: break;
    }
}

void Controller::SearchMode() {
    const HeapID now = model_.get;
    int&rootx = model_.rootPosition[now].first;
    int&rooty = model_.rootPosition[now].second;

    switch (event.type) {
        case SDL_QUIT: isquit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                MouseX = event.motion.x;
                MouseY = event.motion.y;
                showFibHeap(now, rootx, rooty, false, false, 0);
                highlight(target);
                drawInput();
                Context::Inst().renderer.Present();
            }

            break;
        case SDL_KEYDOWN: {
            bool ismove = false;
            switch (event.key.keysym.sym) {
                case SDLK_b:
                    mode = build;
                    target = nullptr;
                    break;
                case SDLK_i:
                    mode = insert;
                    target = nullptr;
                    break;

                case SDLK_x:
                    interval++;
                    break;
                case SDLK_z:
                    if (interval > 0) {
                        interval--;
                    }
                    break;
                case SDLK_RIGHT:
                    if (target == nullptr) {
                        break;
                    }
                    target = target->right;
                    break;
                case SDLK_LEFT:
                    if (target == nullptr) {
                        break;
                    }
                    target = target->left;
                    break;
                case SDLK_UP: {
                    if (target == nullptr) {
                        break;
                    }
                    target = target->parent;
                }
                break;
                case SDLK_DOWN:
                    if (target == nullptr) {
                        target = model_.getRoot();
                    }
                    else {
                        target = target->child;
                        if (target == nullptr) {
                            target = model_.getRoot(); //Heaplist[now].heap_min;
                        }
                    }
                    break;


                case SDLK_0:
                    if (!Input.empty())
                        input('0');
                    break;
                case SDLK_1:
                    input('1');
                    break;
                case SDLK_2:
                    input('2');
                    break;
                case SDLK_3:
                    input('3');
                    break;
                case SDLK_4:
                    input('4');
                    break;
                case SDLK_5:
                    input('5');
                    break;
                case SDLK_6:
                    input('6');
                    break;
                case SDLK_7:
                    input('7');
                    break;
                case SDLK_8:
                    input('8');
                    break;
                case SDLK_9:
                    input('9');
                    break;
                case SDLK_BACKSPACE:
                    if (!Input.empty()) {
                        Input.pop_back();
                        ismove = true;
                    }
                    break;
                case SDLK_RETURN:
                    if (Input.empty()) {
                        break;
                    }
                    target = model_.searchNode(stoi(Input)); //Heaplist[now].search(stoi(Input));
                    Input.clear();
                    break;

                case SDLK_d: {
                    if (target == nullptr) {
                        break;
                    }
                    ismove = true;
                    if (Input.empty())
                        //decreaseKey(now, target, 0);
                        model_.decreaseKey(target, 0);
                    else
                        model_.decreaseKey(target, stoi(Input));
                    //decreaseKey(now, target, stoi(Input));
                    Input.clear();
                    break;
                }
                case SDLK_r: {
                    if (target == nullptr) {
                        break;
                    }
                    ismove = true;
                    model_.remove(target);
                    target=nullptr;
                    break;
                }
                default: break;
            }
            Context::Inst().Clear();
            showFibHeap(now, rootx, rooty, ismove, false, interval);
            highlight(target);
            drawInput();
            Context::Inst().renderer.Present();
            break;
        }

        default: break;
    }
}

void Controller::BuildMode() {
    HeapID&get = model_.get;
    HeapID&other = model_.other;
    auto&pos = model_.rootPosition;
    //int&rootx =  rootPosition[now].first;
    //int&rooty =  rootPosition[now].second;

    switch (event.type) {
        case SDL_QUIT: isquit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            Context::Inst().Clear();
            if (event.button.button == SDL_BUTTON_LEFT) {
                MouseX = event.motion.x;
                MouseY = event.motion.y;
                //HeapID get_=get;
                get = model_.get_heap_id(MouseX, MouseY);
                //if(get==get_) {
                //get=-1;
                //}
                if (get == -1) {
                    Context::Inst().drawNULL(MouseX, MouseY);
                    other = -1;
                }
            }
            else if (event.button.button == SDL_BUTTON_RIGHT) {
                if (get != -1) {
                    MouseX = event.motion.x;
                    MouseY = event.motion.y;
                    other = model_.get_heap_id(MouseX, MouseY);
                    //if (other == get||other==other_) {
                    //other = -1;
                    //}
                }
            }
            for (HeapID i = 0; i < model_.capasity(); i++) {
                if (model_.exist[i])
                    showFibHeap(i, pos[i].first, pos[i].second, false, i == get || i == other, 0);
            }
            Context::Inst().renderer.Present();
            break;
        case SDL_KEYDOWN: {
            bool ismove = false;
            switch (event.key.keysym.sym) {
                case SDLK_i:
                    mode = insert;
                    other = -1;
                    if (get == -1) {
                        model_.addHeap(MouseX, MouseY);
                    }
                    break;

                case SDLK_s:
                    mode = search;
                    other = -1;
                    if (get == -1) {
                        model_.addHeap(MouseX, MouseY);
                        mode = insert;
                    }
                    break;

                case SDLK_x:
                    interval++;
                    break;
                case SDLK_z:
                    if (interval > 0) {
                        interval--;
                    }
                    break;
                case SDLK_RIGHT:
                    pos[get].first += 10;
                    ismove = true;
                    break;
                case SDLK_LEFT:
                    pos[get].first -= 10;
                    ismove = true;
                    break;
                case SDLK_UP:
                    pos[get].second -= 10;
                    ismove = true;
                    break;
                case SDLK_DOWN:
                    pos[get].second += 10;
                    ismove = true;
                    break;
                case SDLK_RETURN:
                    if (get == -1 || other == -1) {
                        break;
                    }
                    model_.HeapUnion(get, other);
                    ismove = true;
                    showFibHeap(get, pos[get].first, pos[get].second, ismove, true, interval);
                //Heaplist[get].heapUnion(Heaplist[other]);
                // exist[other]=false;
                //if(get>other)
                    break;

                default: break;
            }
            Context::Inst().Clear();
            for (HeapID i = 0; i < model_.capasity(); i++) {
                showFibHeap(i, pos[i].first, pos[i].second, ismove, i == get || i == other, 0);
            }
            Context::Inst().renderer.Present();
            break;
        }

        default: break;
    }
}


void Controller::run() {
    while (!isquit) {
        MessageHandling();
    }
}

void Controller::MessageHandling() {
    while (SDL_PollEvent(&event)) {
        switch (mode) {
            case insert: InsertMode();
                break;
            case search: SearchMode();
                break;
            case build: BuildMode();
                break;
            default: break;
        }
    }
}


void Controller::highlight(Multi_node* target) {
    if (target == nullptr) {
        return;
    }
    if (model_.searchID(target) == -1) {
        return;
    }
    Context::Inst().highlightNode(model_.Visual_Heap_list[model_.get], model_.searchID(target));
}

void Controller::showFibHeap(HeapID id, int rootX, int rootY, bool ismove, bool bright, int interval) {
    auto&ctx = Context::Inst();
    auto& V_Heap = model_.Visual_Heap_list[id];
    if (ismove) {
        std::vector<View::Multi_node> temp = V_Heap;
        model_.update_VisualHeap(id, rootX, rootY);
        for (int i = 0; i < V_Heap.size(); i++) {
            if (!temp[i].exist && V_Heap[i].exist) {
                temp[i].text = V_Heap[i].text;
                temp[i].x = MouseX;
                temp[i].y = MouseY;
            }
            temp[i].exist = V_Heap[i].exist;
            temp[i].father_id = V_Heap[i].father_id;
            temp[i].brother_id = V_Heap[i].brother_id;
        }
        if (interval != 0) {
            bool canmove;
            do {
                canmove = false;
                ctx.Clear();
                ctx.drawTree(temp, bright);
                drawPotential();
                for (int i = 0; i < V_Heap.size(); i++) {
                    if (!V_Heap[i].exist) {
                        continue;
                    }
                    if (temp[i].x != V_Heap[i].x) {
                        canmove = true;
                        temp[i].x = V_Heap[i].x - (V_Heap[i].x - temp[i].x) / 10 * 9;
                    }

                    if (temp[i].y != V_Heap[i].y) {
                        canmove = true;
                        temp[i].y = V_Heap[i].y - (V_Heap[i].y - temp[i].y) / 10 * 9;
                    }
                }
                SDL_Delay(interval);
                ctx.renderer.Present();
            }
            while (canmove);
            ctx.Clear();
        }
        //if(interval)
        //ctx.Clear();
    }
    //ctx.Clear();
    drawPotential();
    ctx.drawTree(V_Heap, bright);
}


void Controller::drawInput() const {
    if (Input.empty()) {
        return;
    }
    Context::Inst().drawInput(Input, MouseX, MouseY);
}

void Controller::drawPotential() {
    if(mode!=build)
        Context::Inst().drawP(model_.P);
}

void Controller::input(char x) {
    if (Input.size() < 4)
        Input.push_back(x);
}
