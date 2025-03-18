#pragma once

#include <ostream>

enum class Couleur {
    Blanc,
    Noir
};

std::ostream& operator<<(std::ostream& os, Couleur c);