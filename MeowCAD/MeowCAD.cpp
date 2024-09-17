#include "Engine.h"

// discreate GPU 
#include <windows.h>
extern "C" {
    _declspec(dllexport) DWORD NvOptimusEnablement = 1;
    _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}


int main() {
    Engine::get().init();
}

// ToDo 
// 
// Understand and implement Command pattern
// https://refactoring.guru/design-patterns/command
// 