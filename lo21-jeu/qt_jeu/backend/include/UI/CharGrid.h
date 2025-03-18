#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <sstream>

class CharGrid
{
private:
    int width;
    int height;
    std::vector<std::vector<char>> grid;

    void prefillGrid();
public:
    CharGrid(int width, int height);
    void addString(int x, int y, const std::string& input);
    void addChar(int x, int y, char input);
    char getChar(int x, int y) const;
    std::string print(bool trimToBoundingBox) const;
};

