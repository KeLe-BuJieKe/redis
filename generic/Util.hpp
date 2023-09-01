#pragma once

#include <iostream>

template<class T>
void printContainer(const T& container) {
    for (const auto& elem : container) {
        std::cout << elem << std::endl;
    }
}