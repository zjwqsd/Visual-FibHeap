//
// Created by zhang on 2024/1/27.
//
#include"Model/Model.h"

//void Model::add_Heapnode(HeapID id, int val) {

//}
//void Model::add_Heapnode(HeapID id, int val) {

//}

void Model::add_Heapnode(int val) {
    add_Heapnode(Heaplist[get], Heap_Info_list[get], Visual_Heap_list[get], val);
}

void Model::deleteFibNode(int val) {
    deleteFibNode(Heaplist[get], Heap_Info_list[get], val);
}

void Model::ExtraMin() {
    ExtraMin(Heaplist[get], Heap_Info_list[get]);
}

void Model::decreaseKey(Multi_node* t, int val) {
    decreaseKey(Heaplist[get], Heap_Info_list[get], t, val);
}

void Model::remove(Multi_node* t) {
    remove(Heaplist[get], Heap_Info_list[get], t);
}

void Model::init_Fib() {
    init_Fib(Heaplist[get], Heap_Info_list[get], Visual_Heap_list[get]);
}

void Model::init_Fib(FibHeap&heap, Heap_info&info, Visual_Heap&V_heap) {
    heap.clear();
    info.clear();
    V_heap.clear();
    //this->Input.clear();
}

void Model::addHeap(int x, int y) {
    Heaplist.emplace_back();
    Heap_Info_list.emplace_back();
    Visual_Heap_list.emplace_back();
    get = Heaplist.size() - 1;
    exist.push_back(true);
    rootPosition.emplace_back(x, y);
}


void Model::add_Heapnode(FibHeap&heap, Heap_info&info, Visual_Heap&V_heap, int val) {
    heap.insert(val);
    get_Heapinformation(heap, info);
    V_heap.push_back({false, false, false, 0, 0, -1, -1, ""});
}


void Model::deleteFibNode(FibHeap&heap, Heap_info&info, int val) {
    if (heap.heap_min == nullptr) {
        return;
    }
    heap.remove(val);
    get_Heapinformation(heap, info);
}

void Model::ExtraMin(FibHeap&heap, Heap_info&info) {
    if (heap.heap_min == nullptr) {
        return;
    }
    heap.extractMin();
    get_Heapinformation(heap, info);
}

void Model::decreaseKey(FibHeap&heap, Heap_info&info, Multi_node* t, int val) {
    if (heap.heap_min == nullptr) {
        return;
    }
    if (t == nullptr) {
        return;
    }
    heap.decreaseKey(t, val);
    get_Heapinformation(heap, info);
}

void Model::remove(FibHeap&heap, Heap_info&info, Multi_node* t) {
    if (heap.heap_min == nullptr) {
        return;
    }
    if (t == nullptr) {
        return;
    }
    heap.decreaseKey(t, 0);
    heap.extractMin();
    get_Heapinformation(heap, info);
    target = nullptr;
}

void Model::update_VisualHeap(const FibHeap&heap, Heap_info&info, Visual_Heap&V_Heap, int rootX, int rootY) const {
   // auto&ctx = Context::Inst();
    //if (ismove) {
        //std::vector<View::Multi_node> temp = V_Heap;
        for (auto&it: V_Heap) {
            it.exist = false;
        }
        std::queue<Multi_node *> Q;
        if (heap.heap_min != nullptr) {
            Q.push(heap.heap_min);
            V_Heap[info[heap.heap_min].id].x = rootX;
            V_Heap[info[heap.heap_min].id].y = rootY;
            V_Heap[info[heap.heap_min].id].father_id = -1;
            V_Heap[info[heap.heap_min].id].brother_id = -1;
            V_Heap[info[heap.heap_min].id].mark = heap.heap_min->mark;
        }
        while (!Q.empty()) {
            Multi_node* cur = Q.front();
            V_Heap[info[cur].id].exist = true;
            V_Heap[info[cur].id].text = std::to_string(cur->val);
            V_Heap[info[cur].id].mark = cur->mark;
            Q.pop();

            if (cur->child != nullptr) {
                V_Heap[info[cur->child].id].x =
                        V_Heap[info[cur].id].x;
                V_Heap[info[cur->child].id].y =
                        V_Heap[info[cur].id].y + 40;
                V_Heap[info[cur->child].id].father_id =
                        info[cur].id;
                V_Heap[info[cur->child].id].brother_id = -1;
                Q.push(cur->child);
            }
            if (info[cur->right].left_id != -1) {
                V_Heap[info[cur->right].id].x =
                        V_Heap[info[cur].id].x + info[cur].width * 50;
                V_Heap[info[cur->right].id].y =
                        V_Heap[info[cur].id].y;
                V_Heap[info[cur->right].id].father_id =
                        V_Heap[info[cur].id].father_id;
                V_Heap[info[cur->right].id].brother_id =
                        info[cur].id;
                Q.push(cur->right);
            }
        }
        //for (int i = 0; i < V_Heap.size(); i++) {
            //if (!temp[i].exist && V_Heap[i].exist) {
                //temp[i].text = V_Heap[i].text;
                //temp[i].x = MouseX;
                //temp[i].y = MouseY;
            //}
            //temp[i].exist = V_Heap[i].exist;
            //temp[i].father_id = V_Heap[i].father_id;
            //temp[i].brother_id = V_Heap[i].brother_id;
        //}
    /*
        if (interval != 0) {
            bool canmove;
            do {
                canmove = false;
                //ctx.Clear();
                //ctx.drawTree(temp, bright);
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
                //ctx.renderer.Present();
            }
            while (canmove);
            //ctx.Clear();
        }
        //if(interval)
        //ctx.Clear();
   // }
    //ctx.Clear();

    //ctx.drawTree(V_Heap, bright);
    */
}


//void Model::drawInput() const {
    //if (Input.empty()) {
    //    return;
   // }
   // Context::Inst().drawInput(Input, MouseX, MouseY);
//}

void Model::get_Heapinformation(const FibHeap&heap, Heap_info&info) {
    P=0;
    Multi_node* root = heap.heap_min;
    if (root == nullptr) {
        return;
    }
    if (heap.heap_min->parent != nullptr) {
        SDL_Log("root error");
    }

    if (info.find(root) == info.end()) {
        int capasity = static_cast<int>(info.size());
        info.insert({root, {capasity, root->val}});
    }
    info[root].father_id = -1;
    info[root].left_id = -1;
    traverse(root, heap.heap_min, info);
    SDL_Log("%d",P);
}

int Model::getVal(const HeapID id, const int x, const int y) const {
    for (auto&it: Visual_Heap_list[id]) {
        if (!it.exist) {
            continue;
        }
        const int w = 10 * static_cast<int>(it.text.length());
        constexpr int h = 20;
        if (-w / 2 <= x - it.x && x - it.x <= w / 2 && -h / 2 <= y - it.y && y - it.y <= h / 2) {
            return stoi(it.text);
        }
    }
    return 10000;
}

HeapID Model::get_heap_id(int x, int y) {
    int n = rootPosition.size();
    for (int i = 0; i < n; i++) {
        if (!exist[i]) {
            continue;
        }
        if (Heaplist[i].heap_min == nullptr) {
            continue;
        }
        const int w = 10 * static_cast<int>(std::to_string(Heaplist[i].heap_min->val).length());
        constexpr int h = 20;
        int ix = rootPosition[i].first;
        int iy = rootPosition[i].second;
        if ((-w / 2 <= x - ix && x - ix <= w / 2 && -h / 2 <= y - iy && y - iy <= h / 2)) {
            return i;
        }
    }
    return -1;
}

void Model::traverse(Multi_node* root, Multi_node* first, Heap_info&info) {
    if(root->parent==nullptr) {
        P+=1;
    }
    if(root->mark) {
        P+=2;
    }
    if (root->right != first) {
        if (info.find(root->right) == info.end()) {
            int capasity = static_cast<int>(info.size());
            info.insert({root->right, {capasity, root->right->val}});
        }
        if (root->parent != first->parent) {
            SDL_Log("%d father error", root->parent);
        }
        info[root->right].left_id = info[root].id;
        info[root->right].father_id = info[root->right].father_id;
        info[root].right_id = info[root->right].id;
        traverse(root->right, first, info);
    }
    else {
        info[root].right_id = -1;
    }
    if (root->child != nullptr) {
        if (root->child->parent != root) {
            SDL_Log("%d father error", root->val);
        }
        int capasity = static_cast<int>(info.size());
        if (info.find(root->child) == info.end()) {
            info.insert({root->child, {capasity, root->child->val}});
        }
        info[root->child].father_id = info[root].id;
        info[root->child].left_id = -1;
        info[root].son_id = -1;
        traverse(root->child, root->child, info);
    }
    int height = 0;
    int width = 0;
    int cnt = 0;
    for (Multi_node* p = root->child; p != nullptr; p = p->right, cnt++) {
        height = 1 + std::max(height, info[p].height);
        width += info[p].width;
        if (p->right == root->child) {
            cnt++;
            break;
        }
    }
    if (cnt != root->degree) {
        SDL_Log("%d degree error: degree is %d,cnt is %d", root->val, root->degree, cnt);
    }
    else if (root->degree > 1 + std::log2(Heaplist[get].n)) {
        SDL_Log("%d degree is bigger than 1+log %d", root->val, 1 + std::log2(Heaplist[get].n));
    }
    info[root].height = height;
    info[root].width = width > 0 ? width : 1;
}
