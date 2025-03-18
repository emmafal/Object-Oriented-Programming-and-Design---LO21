#pragma once
#include "HexPrinter.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <algorithm>// Assuming you have this header file
#include "CharGrid.h"

class AsciiBoard
{
private:
	int width;
	int height;
	HexPrinter printer;
	CharGrid grid;

	CharGrid createGrid();
	std::string getVerticalLine(char filler, int contentLength) const;
	std::string printBoard(bool wrapInBox) const;
	std::vector<std::string> split(const std::string& str, char delimiter) const;

public:
	AsciiBoard(int minQ, int maxQ, int minR, int maxR, const HexPrinter& printer);
	void addHex(const std::string& textLine1, const std::string& textLine2, char fillerChar, int hexQ, int hexR);
	std::string prettyPrint(bool wrapInBox) const;
};

