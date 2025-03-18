#include "HexPrinter.h"
#include <algorithm>
#include <string>
#include <locale>
#include <array>


const std::string HexPrinter::TEMPLATE = "     /#\\     \n" // 0 - 13
"   /# # #\\   \n"
" /# # # # #\\ \n"
"|# XXXXXXX #|\n"
"|# YYYYYYY #|\n"
"|# # # # # #|\n"
" \\# # # # #/ \n"
"   \\# # #/   \n"
"     \\#/     \n";

std::string HexPrinter::restrictToLength(const std::string& str, int length) {
    std::string result = "  ";
    if (!str.empty()) {
        if (str.length() > length) {
            std::locale loc("");
            std::string upperStr = loc.name();
            std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
            result = upperStr.substr(0, length);
        }
        else if (str.length() < length) {
            std::locale loc("");
            std::string upperStr = loc.name();
            std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
            result = pad(upperStr, length - str.length());
        }
        else {
            result = str;
        }
    }
    return result;
}
std::string HexPrinter::pad(const std::string& str, int size) {
    std::string s = str;
    int n = size;
    while (n > 0) {
        if (n % 2 == 0) {
            s = " " + s;
        }
        else {
            s = s + " ";
        }
        n--;
    }
    return s;
}

std::string HexPrinter::getHex(std::string textLine1, std::string textLine2, char fillerChar) {
	std::string line1 = textLine1;
	std::string line2 = textLine2;
	std::string hex = TEMPLATE;
    line1 = restrictToLength(line1, 7);
    line2 = restrictToLength(line2, 7);
    size_t start_1 = hex.find("XXXXXXX");
    size_t start_2 = hex.find("YYYYYYY");
    hex.replace(start_1,7,line1);
    hex.replace(start_2,7,line2);
    size_t start_pos= 0;
    while ((start_pos = hex.find("#", start_pos)) != std::string::npos) {
        std::string fs(1,fillerChar);
        hex.replace(start_pos, 1, fs);
        start_pos += 1; // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
    return hex;
}

std::array<int, 2> HexPrinter::mapHexCoordsToCharCoords(int q, int r) {
    std::array<int, 2> result;
    result[0] = (width - bordersLength) * q + r * (height - sideHeight); // q * (width - side)
    result[1] = (height - sideHeight) * r; // height/2 * q + (height - 1) * r
    return result;
}

std::array<int, 2> HexPrinter::getMapSizeInChars(int hexWidth, int hexHeight) {
    int widthInChars = hexWidth * width + sideWidth + hexHeight * sideWidth;
    int heightInChars = hexHeight * (height - sideHeight) + sideHeight;
    return { widthInChars, heightInChars };
}