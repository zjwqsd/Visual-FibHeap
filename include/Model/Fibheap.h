#ifndef FIBHEAP_H
#define FIBHEAP_H
#include <cmath>

struct Multi_node {
    Multi_node* parent;
    Multi_node* child;
    Multi_node* left;
    Multi_node* right;
    int val;
    int degree; //degree of children
    bool mark; //whether lose any child
    Multi_node() : parent(nullptr), child(nullptr), left(this), right(this),
             val(0), degree(0), mark(false) {
    }
};

class FibHeap {
public:
    Multi_node* heap_min; //pointer to the minimum node of heap
    int n;

private :
    /*
    Window(Window&& other)  noexcept {
        window_ = other.window_;
        other.window_= nullptr;
    }*/
    static void listAdd(Multi_node* &r, Multi_node* p); //add p to r

    static void listdelete(Multi_node* p);

    static void listUnion(Multi_node* x, Multi_node* y); //add x and y

    [[nodiscard]] int Dn() const { return 1+ static_cast<int>(std::log2(n)); } //当所有根都合并到一棵树上时，dn最大，为log2(n), 参考二项树

    void consolidate();

    static void heapLink(Multi_node* y, Multi_node* x);

    void cut(Multi_node* x, Multi_node* y);

    void cascadingCut(Multi_node* y);

    Multi_node* search(Multi_node* r, int k); //search is not good in heap

public :
    FibHeap() : heap_min(nullptr), n(0) {
    }

    FibHeap(FibHeap&&other)noexcept {
        heap_min=other.heap_min;
        n=other.n;
        other.heap_min=nullptr;
    }

    ~FibHeap();
    void insert(int k);

    int extractMin(); //get minimum node and delete it
    [[nodiscard]] int minimum() const { return heap_min->val; }

    void decreaseKey(Multi_node* x, int k);

    void remove(int k);

    void heapUnion(FibHeap&b);
    void clear();
    Multi_node* search(int k) { return search(heap_min, k) ; }
    [[nodiscard]] bool empty() const { return n == 0; }
};
#endif // FIBHEAP_H
