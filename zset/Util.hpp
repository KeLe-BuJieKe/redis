#pragma once
#include <iostream>
#include <string>
template<class T>
inline void printContainer(const T& container) {
    for (const auto& elem : container) {
        std::cout << elem << std::endl;
    }
}


template<>
inline void printContainer<std::vector<std::pair<std::string, double>>>(const std::vector<std::pair<std::string, double>>& container) {
    for (const auto& elem : container) {
        std::cout << elem.first  << " : " << elem.second << std::endl;
    }
}

template<class T>
inline void printContainerOptional(const T& container) {
    for (const auto& elem : container) {
        if (elem.has_value()) {
            std::cout << elem.value() << std::endl;
        }
        else {
            std::cout << "元素无效" << std::endl;
        }
    }
}