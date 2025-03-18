#pragma once
#include <string>
#include <array>

class HexPrinter
{
private:
	int width = 14;
	int height = 9;
	int sideWidth = 6; // Size from center to left/right border
	int sideHeight = 3; // Size from top to left/right border
	int bordersLength = 2; // Size of the combined left/right borders
	static const std::string TEMPLATE;
	std::string restrictToLength(const std::string& str, int length);
	std::string pad(const std::string& str, int size);
public:
	std::string getHex(std::string textLine1, std::string textLine2, char fillerChar);
	std::array<int, 2> mapHexCoordsToCharCoords(int q, int r);
	std::array<int, 2> getMapSizeInChars(int hexWidth, int hexHeight);


};

