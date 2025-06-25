//
// Created by dakus on 05/05/2025.
//

#ifndef UTILS_H
#define UTILS_H
#include <math.h>
#include <algorithm>
#include <SFML/System/Vector2.hpp>

namespace Utils {
    inline float lenght(const sf::Vector2f &vec) {
        return std::sqrt(vec.x * vec.x + vec.y * vec.y);
    }
    inline sf::Vector2f normalize(const sf::Vector2f &vec) {
        float len = lenght(vec);
        if (len != 0.f)
            return vec / len;
        return sf::Vector2f(0.f, 0.f);
    }
}

#endif //UTILS_H
