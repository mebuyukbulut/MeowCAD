#pragma once
#include "Shape3D.h"
class Cylinder :
    public Shape3D
{
    float height{ 2 };
    float radius{ 1 };
    int ngon{ 32 };
    void generate() override;
public:
    Cylinder() = default;
    Cylinder(float radius, float height, int ngon = 32) 
        : radius{ radius }, height{ height }, ngon{ ngon } {}
};

