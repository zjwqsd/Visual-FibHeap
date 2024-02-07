//
// Created by zhang on 2023/12/13.
//

#ifndef PCH_H
#define PCH_H
#include<SDL2/SDL.h>
#include<string>
#include<vector>
#include <memory>
#include<map>
#include<queue>
#include<random>

struct Node_information {
    const int id;
    const int val;
    int width;
    int height;
    int father_id;
    int left_id;
    int right_id;
    int son_id;

    Node_information(const int id, const int val): id(id), val(val), width(1), height(0), father_id(-1), left_id(-1),
                                                   right_id(-1), son_id(-1) {
    }

    Node_information(): id(-1), val(0), width(1), height(0), father_id(-1), left_id(-1), right_id(-1), son_id(-1) {
    }
};

namespace View {
    struct Multi_node {
        bool exist = false;
        bool bright = true;
        bool mark = false;
        int x;
        int y;
        int father_id;
        int brother_id;
        std::string text;
    };
}
#endif //PCH_H
