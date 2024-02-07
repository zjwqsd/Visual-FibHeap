//
// Created by zhang on 2023/12/20.
//
#include "Model/Fibheap.h"
#include<vector>
#include<queue>
#include <SDL2/SDL_log.h>

void FibHeap::listAdd(Multi_node* &r, Multi_node* p) {
    if (r == nullptr) {
        r = p;
        r->left = r;
        r->right = r;
    }
    else {
        Multi_node* x = r; //去引用
        p->right = x->right;
        p->left = x;
        x->right->left = p;
        x->right = p;
    }
}

void FibHeap::listdelete(Multi_node* p) {
    //if(p->parent != nullptr && p->parent->child == p)
    //    p->parent->child = nullptr;
    //p->left->right = p->right;
   // p->right->left = p->left;
    Multi_node *x = nullptr;
    if(p->right != nullptr) {
        x = (p->right == p) ? x : p->right;
        p->right->left = p->left;
    }
    if(p->left != nullptr) {
        x = (p->left == p) ? x : p->left;
        p->left->right = p->right;
    }
    if(p->parent != nullptr)
        if(p->parent->child == p)
            p->parent->child = x;
}

 void FibHeap::listUnion(Multi_node* x, Multi_node* y) {
    if (x == nullptr)
        x = y;
    else {
        Multi_node* tail = x->left;
        x->left->right = y;
        y->left->right = x;
        x->left = y->left;
        y->left = tail;
    }
}

FibHeap::~FibHeap() {

    clear();
}

 void FibHeap::insert(int k) {
    auto* p = new Multi_node;
    p->val = k;
    listAdd(heap_min, p);
    if (heap_min->val > k) {
        heap_min = p;
    }
    ++n;
}

void FibHeap::heapLink(Multi_node* y, Multi_node* x) {
    listdelete(y);
    listAdd(x->child, y);
    ++x->degree;
    y->mark = false;
    y->parent=x;
}

 void FibHeap::consolidate() {
    std::vector<Multi_node *> a(n, nullptr);
    Multi_node *x, *y, *z;
    int d;
    auto* sentry = new Multi_node;
    listAdd(heap_min->left, sentry); //add a sentry
    for (x = heap_min; x != sentry; x = z) {
        z = x->right; //防止x被link到y上，导致x-right无法指向正确的位置，所以先保存
        d = x->degree;
        while (a[d] != nullptr) {
            y = a[d];
            if (x->val > y->val)
                std::swap(x, y);
            heapLink(y, x);
            a[d] = nullptr;
            ++d;
        }
        a[d] = x;
    }
    heap_min = nullptr;
    for (auto & i : a) {
        if (i != nullptr) {
            listAdd(heap_min, i);
            if (i->val < heap_min->val)
                heap_min = i;
        }
    }
    delete sentry;
}

 int FibHeap::extractMin() {
    int ret = 0;
    Multi_node* p = heap_min;
    if (p) {
        ret = p->val;
        if (p->child) {
            Multi_node* x = p->child;
            Multi_node* y = x->right;
            for (int i = 0; i < p->degree; ++i) {
                listAdd(heap_min, x);
                x->parent = nullptr;
                x = y;
                y = y->right;
            }
        }
        if (p->right == p) //the child of p is empty, and p is the only one in root list
            heap_min = nullptr;
        else {
            heap_min = p->right;
            listdelete(p);
            consolidate();
        }
        delete p;
        --n;
    }
    return ret;
}

 void FibHeap::cut(Multi_node* x, Multi_node* y) {
    listdelete(x);
    --y->degree;
    listAdd(heap_min, x);
    x->parent = nullptr;
    x->mark = false;
}

 void FibHeap::cascadingCut(Multi_node* y) {
    Multi_node* z = y->parent;
    if (z) {
        if (y->mark == false)
            y->mark = true;
        else {
            cut(y, z);
            cascadingCut(z);
        }
    }
}

 void FibHeap::decreaseKey(Multi_node* x, int k) {
    if (k >= x->val)
        return;
    x->val = k;
    Multi_node* y = x->parent;
    if (y && y->val > x->val) {
        cut(x, y);
        cascadingCut(y);

    }
    if (x->val < heap_min->val)
        heap_min = x;
}

 void FibHeap::remove(int k) {
    Multi_node* p = search(heap_min, k);
    if (p == nullptr)
        return;
    //SDL_Log("%d",p->val);
    decreaseKey(p, 0);
    extractMin();
}

 void FibHeap::heapUnion(FibHeap&b) {
    //can't use b any more
    if (b.heap_min == nullptr)
        return;
    listUnion(heap_min, b.heap_min);
    if (heap_min->val > b.heap_min->val)
        heap_min = b.heap_min;
    n += b.n;
    b.heap_min=nullptr;
}

void FibHeap::clear() {
    if(heap_min==nullptr)
        return;
    std::queue<Multi_node*>Q;
    heap_min->left->right=nullptr;
    Q.push(heap_min);
    while (!Q.empty()) {
        Multi_node* cur = Q.front();
        Q.pop();
        if(cur->right!=nullptr) {
            Q.push(cur->right);
        }
        if(cur->child!=nullptr) {
            cur->child-> left->right=nullptr;
            Q.push(cur->child);
        }
        delete cur;
    }
    n=0;
    heap_min=nullptr;
}

Multi_node* FibHeap::search(Multi_node* r, int k) {
    if (r == nullptr)
        return r;
    Multi_node *x = r, *y;
    do {
        if (x->val == k)
            return x;
        else if (x->val < k) {
            y = search(x->child, k);
            if (y)
                return y;
        }
        x = x->right;
    }
    while (x != r);

    return nullptr;
}
