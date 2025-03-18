#include "CharGrid.h"


void CharGrid::prefillGrid() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            addChar(j, i, ' ');
        }
    }
}

CharGrid::CharGrid(int width, int height) : width(width), height(height), grid(height, std::vector<char>(width)) {
    prefillGrid();
}

void CharGrid::addString(int x, int y, const std::string& input) {
    if (input.empty()) return;
    for (size_t i = 0; i < input.length(); ++i) {
        addChar(x + i, y, input[i]);
    }
}

void CharGrid::addChar(int x, int y, char input) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        int maxWidth = width - 1;
        int maxHeight = height - 1;
        throw std::out_of_range("(" + std::to_string(x) + "," + std::to_string(y) + ") is outside (" + std::to_string(maxWidth) + "," + std::to_string(maxHeight) + ")");
    }
    grid[y][x] = input;
}

char CharGrid::getChar(int x, int y) const {
    return grid[y][x];
}

std::string CharGrid::print(bool trimToBoundingBox) const {
    int leftBound = trimToBoundingBox ? width - 1 : 0;
    int rightBound = trimToBoundingBox ? 0 : width - 1;
    int topBound = trimToBoundingBox ? height - 1 : 0;
    int bottomBound = trimToBoundingBox ? 0 : height - 1;

    if (trimToBoundingBox) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                char c = grid[i][j];
                if (c != ' ') {
                    leftBound = std::min(leftBound, j);
                    rightBound = std::max(rightBound, j);
                    topBound = std::min(topBound, i);
                    bottomBound = std::max(bottomBound, i);
                }
            }
        }
    }

    std::ostringstream builder;
    for (int i = topBound; i <= bottomBound; ++i) {
        for (int j = leftBound; j <= rightBound; ++j) {
            builder << grid[i][j];
        }
        builder << "\n";
    }
    return builder.str();
}