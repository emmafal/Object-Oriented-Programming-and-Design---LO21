#include "AsciiBoard.h"

AsciiBoard::AsciiBoard(int minQ, int maxQ, int minR, int maxR, const HexPrinter& printer)
    : width(maxQ - minQ + 1), height(maxR - minR + 1), printer(printer), grid(createGrid()) {};

CharGrid AsciiBoard::createGrid() {
    auto gridSize = printer.getMapSizeInChars(width, height);
    return CharGrid(gridSize[0], gridSize[1]);
}

std::string AsciiBoard::getVerticalLine(char filler, int contentLength) const {
    std::string verticalLine = "| ";
    for (int i = 0; i < contentLength; ++i) {
        verticalLine += (i % 2 == 0) ? filler : ' ';
    }
    return verticalLine + " |\n";
}

std::string AsciiBoard::printBoard(bool wrapInBox) const {
    if (wrapInBox) {
        std::ostringstream sb;

        auto lines = split(grid.print(true), '\n');
        int contentLength = lines.empty() ? 0 : lines[0].length();
        std::string verticalLine = getVerticalLine('=', contentLength);
        std::string spacerLine = getVerticalLine(' ', contentLength);

        sb << verticalLine;
        for (const auto& line : lines) {
            sb << "| " << line << " |\n";
        }

       
        sb << spacerLine;
       
        return sb.str();
    }
    else {
        return grid.print(true);
    }
}

std::vector<std::string> AsciiBoard::split(const std::string& str, char delimiter) const {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void AsciiBoard::addHex(const std::string& textLine1, const std::string& textLine2, char fillerChar, int hexQ, int hexR) {
    std::string hex = printer.getHex(textLine1, textLine2, fillerChar);
    auto charCoordinates = printer.mapHexCoordsToCharCoords(hexQ, hexR);
    auto lines = split(hex, '\n');
    for (size_t i = 0; i < lines.size(); ++i) {
        const std::string& content = lines[i];
        for (size_t j = 0; j < content.length(); ++j) {
            int x = charCoordinates[0] + j;
            int y = charCoordinates[1] + i;

            if (grid.getChar(x, y) == ' ') {
                grid.addChar(x, y, content[j]);
            }
        }
    }
}

std::string AsciiBoard::prettyPrint(bool wrapInBox) const {
    return printBoard(wrapInBox);
}