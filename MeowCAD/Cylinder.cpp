#include "Cylinder.h"
#include <glm/glm.hpp>

#include <iterator>
#include <algorithm>
#include <iostream>

void Cylinder::generate(){
    const float PI = 3.14159265;

    std::vector<Vertex> vertices;

    for (int i{}; i < ngon+1; i++) {
        Vertex v1, v2, v3, v4;


        glm::vec3 n1, n2, n3, n4, p1, p2, p3, p4;
        float angle = 360 / ngon * i;
        angle *= PI / 180;

        std::cout 
            << "sin(" << angle << ") = " << sin(angle) << "\t"
            << "cos(" << angle << ") = " << cos(angle) << "\n";

        n1 = glm::vec3(sin(angle), 0, cos(angle));
        n1 = glm::normalize(n1);
        p1 = n1 * radius;
        p1.y = -height / 2.0f;

        n2 = glm::vec3(sin(angle), 0, cos(angle));
        n2 = glm::normalize(n2);
        p2 = n2 * radius;
        p2.y = height / 2.0f;

        angle = 360 / ngon * (i+1);
        angle *= PI / 180;

        n3 = glm::vec3(sin(angle), 0, cos(angle));
        n3 = glm::normalize(n3);
        p3 = n3 * radius;
        p3.y = -height / 2.0f;

        n4 = glm::vec3(sin(angle), 0, cos(angle));
        n4 = glm::normalize(n4);
        p4 = n4 * radius;
        p4.y = height / 2.0f;

        v1.set_position(p1);
        v2.set_position(p2);
        v3.set_position(p3);
        v4.set_position(p4);

        v1.set_normal(n1);
        v2.set_normal(n2);
        v3.set_normal(n3);
        v4.set_normal(n4);

        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);

        vertices.push_back(v3);
        vertices.push_back(v2);
        vertices.push_back(v4);

        Vertex v5, v6;
        v5.set_position(glm::vec3(0, height / 2, 0));
        v6.set_position(glm::vec3(0, -height / 2, 0));

        v4.set_normal(glm::vec3(0, 1, 0));
        v2.set_normal(glm::vec3(0, 1, 0));
        v5.set_normal(glm::vec3(0, 1, 0));

        v3.set_normal(glm::vec3(0, -1, 0));
        v1.set_normal(glm::vec3(0, -1, 0));
        v6.set_normal(glm::vec3(0, -1, 0));


        vertices.push_back(v4);
        vertices.push_back(v2);
        vertices.push_back(v5);

        vertices.push_back(v3);
        vertices.push_back(v1);
        vertices.push_back(v6);
    }

    std::copy(vertices.begin(), vertices.end(), std::back_insert_iterator(data));
}
