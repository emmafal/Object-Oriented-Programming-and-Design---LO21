#include "Direction.h"

const Direction Direction::NW = Direction(0, -1);
const Direction Direction::W = Direction(-1, 0);
const Direction Direction::SW = Direction(-1, 1);
const Direction Direction::NE = Direction(1, -1);
const Direction Direction::E = Direction(1, 0);
const Direction Direction::SE = Direction(0, 1);

const std::vector<Direction> Direction::getDirs()
{
    return {NE, E, SE, SW, W, NW};
}
