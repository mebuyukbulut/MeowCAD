#include "Engine.h"

// discreate GPU 
#include <windows.h>
extern "C" {
    _declspec(dllexport) DWORD NvOptimusEnablement = 1;
    _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}


int main() {
    Engine::get().main();
}

// ToDo 
// Improve shape class and add new child classes 
// - Sphere
// - Cylinder
//  
// Understand and implement Command pattern
// https://refactoring.guru/design-patterns/command
// 
// 
 

// Handle mesh, material vb resource correctly !!!