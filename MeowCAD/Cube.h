#pragma once
#include "Shape3D.h"
#include <iterator>
#include <algorithm>


class Cube :
    public Shape3D
{
    float size{ 1 };
    void generate() override {
        std::vector<Vertex> vertices = {
            // back face 
            {{-1.0f, -1.0f, -1.0f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            {{ 1.0f, -1.0f, -1.0f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
            {{ 1.0f,  1.0f, -1.0f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            {{ 1.0f,  1.0f, -1.0f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            {{-1.0f,  1.0f, -1.0f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            {{-1.0f, -1.0f, -1.0f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            // front face           {},
            {{-1.0f, -1.0f,  1.0f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {0.0f, 0.0f}},
            {{ 1.0f, -1.0f,  1.0f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {1.0f, 0.0f}},
            {{ 1.0f,  1.0f,  1.0f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {1.0f, 1.0f}},
            {{ 1.0f,  1.0f,  1.0f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {1.0f, 1.0f}},
            {{-1.0f,  1.0f,  1.0f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {0.0f, 1.0f}},
            {{-1.0f, -1.0f,  1.0f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {0.0f, 0.0f}},
            //                      {},
            {{-1.0f,  1.0f,  1.0f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {1.0f, 0.0f}},
            {{-1.0f,  1.0f, -1.0f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {1.0f, 1.0f}},
            {{-1.0f, -1.0f, -1.0f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {0.0f, 1.0f}},
            {{-1.0f, -1.0f, -1.0f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {0.0f, 1.0f}},
            {{-1.0f, -1.0f,  1.0f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {0.0f, 0.0f}},
            {{-1.0f,  1.0f,  1.0f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {1.0f, 0.0f}},
            //                      {},
            {{ 1.0f,  1.0f,  1.0f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {1.0f, 0.0f}},
            {{ 1.0f,  1.0f, -1.0f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {1.0f, 1.0f}},
            {{ 1.0f, -1.0f, -1.0f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {0.0f, 1.0f}},
            {{ 1.0f, -1.0f, -1.0f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {0.0f, 1.0f}},
            {{ 1.0f, -1.0f,  1.0f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {0.0f, 0.0f}},
            {{ 1.0f,  1.0f,  1.0f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {1.0f, 0.0f}},
            //                      {},
            {{-1.0f, -1.0f, -1.0f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {0.0f, 1.0f}},
            {{ 1.0f, -1.0f, -1.0f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {1.0f, 1.0f}},
            {{ 1.0f, -1.0f,  1.0f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {1.0f, 0.0f}},
            {{ 1.0f, -1.0f,  1.0f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {1.0f, 0.0f}},
            {{-1.0f, -1.0f,  1.0f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {0.0f, 0.0f}},
            {{-1.0f, -1.0f, -1.0f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {0.0f, 1.0f}},
            //                      {},
            {{-1.0f,  1.0f, -1.0f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {0.0f, 1.0f}},
            {{ 1.0f,  1.0f, -1.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {1.0f, 1.0f}},
            {{ 1.0f,  1.0f,  1.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {1.0f, 0.0f}},
            {{ 1.0f,  1.0f,  1.0f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {1.0f, 0.0f}},
            {{-1.0f,  1.0f,  1.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {0.0f, 0.0f}},
            {{-1.0f,  1.0f, -1.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {0.0f, 1.0f}},
        };
        for (auto& i : vertices)
            i.set_position(i.get_position()* size);

        std::copy(vertices.begin(), vertices.end(), std::back_insert_iterator(data));
    }
public:

    Cube() = default;
    Cube(float size) :size{ size } {}

};
