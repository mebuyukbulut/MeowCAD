#pragma once
#include "Shape3D.h"

class Cube : public Shape3D{
    float size{ 1 };
    void generate() override;
public:
    Cube() = default;
    Cube(float size) :size{ size } {}
};

