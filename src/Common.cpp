#include "Common.hpp"

bool CommonMethods::isValidSymbol(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || (ch == '_');
}

std::string CommonMethods::numberToWords(std::size_t num) 
{
    if (num == 0) 
    {
        return "no";
    }
    switch (num) 
    {
        case 1:
            return "one";
        case 2:
            return "two";
        case 3:
            return "three";
        case 4:
            return "four";
        default:
            return std::to_string(num);
    }
}

std::vector<std::string> CommonMethods::split(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;

    while ((end = str.find(delimiter, start)) != std::string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
    }

    tokens.push_back(str.substr(start));
    return tokens;
}