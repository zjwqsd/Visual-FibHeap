//
// Created by zhang on 2024/1/27.
//

#ifndef MODEL_H
#define MODEL_H
#include "Fibheap.h"
#include "pch.h"
typedef size_t HeapID;
class Model {
public:
    Model() {
        InputX = 300;
        InputY = 400;
        //InputBox = {300, 500, 30, 10};
        Heaplist.emplace_back();
        Heap_Info_list.emplace_back();
        Visual_Heap_list.emplace_back();
        get = 0;
        other = -1;
        exist.emplace_back(true);
        rootPosition.emplace_back(100, 20);
    }

    //typedef size_t HeapID;
    typedef std::map<Multi_node *, Node_information> Heap_info;
    typedef std::vector<View::Multi_node> Visual_Heap;
    std::vector<FibHeap> Heaplist;
    std::vector<Heap_info> Heap_Info_list;
    std::vector<Visual_Heap> Visual_Heap_list;
    HeapID get;
    HeapID other;
    std::vector<std::pair<int, int>> rootPosition;
    std::vector<bool> exist;

    [[nodiscard]] HeapID capasity() const {
        return Heaplist.size();
    }
    Multi_node* target = nullptr;

    void add_Heapnode(int val);

    void add_Heapnode(FibHeap&, Heap_info&, Visual_Heap&, int val);

    void deleteFibNode(int val);

    void deleteFibNode(FibHeap&, Heap_info&, int val);

    void ExtraMin();

    void ExtraMin(FibHeap&, Heap_info&);

    void decreaseKey(Multi_node* t, int val);

    void decreaseKey(FibHeap&, Heap_info&, Multi_node*, int);

    void remove(Multi_node* t);

    void remove(FibHeap&, Heap_info&, Multi_node*);

    void HeapUnion(HeapID i, HeapID j) {
        Visual_Heap_list[i].resize(Visual_Heap_list[i].size() + Heaplist[j].n);
        Heaplist[i].heapUnion(Heaplist[j]);
        exist[j] = false;
        //Heap_Info_list[i].insert(Heap_Info_list[j].begin(),Heap_Info_list[j].end());
        get_Heapinformation(i);
    }

    void init_Fib();

    void init_Fib(FibHeap&heap, Heap_info&, Visual_Heap&);

    void addHeap(int x, int y);

    void get_Heapinformation(const FibHeap&, Heap_info&);

    void get_Heapinformation(HeapID id) {
        get_Heapinformation(Heaplist[id], Heap_Info_list[id]);
    }

    [[nodiscard]] int getVal(HeapID, int x, int y) const;

    HeapID get_heap_id(int x, int y);

    void traverse(Multi_node* root, Multi_node* first, Heap_info&info);

    void update_VisualHeap(const FibHeap&heap, Heap_info&info, Visual_Heap&V_Heap, int rootX, int rootY) const;
    void update_VisualHeap(HeapID id,int x,int y) {
        update_VisualHeap(Heaplist[id],Heap_Info_list[id],Visual_Heap_list[id],x,y);
    }
    HeapID searchID(Multi_node* target) {
        if(Heap_Info_list[get].find(target)==Heap_Info_list[get].end()) {
            return -1;
        }
        return Heap_Info_list[get][target].id;
    }
    Multi_node* searchNode(int val) {
        return Heaplist[get].search(val);
    }
    bool empty(HeapID id) {
        return Heaplist[id].heap_min==nullptr;
    }
    Multi_node* getRoot() {
        return Heaplist[get].heap_min;
    }
    //int get_Potential() {
        //int t=0,m=0;

    //}
    int P = 0;
    int InputX, InputY;
};
#endif //MODEL_H
