#pragma once
#include <string>
#include <vector>

class CommonMethods
{
public:
    static bool isValidSymbol(char ch);
    static std::string numberToWords(std::size_t num);  
    static std::vector<std::string> split(const std::string& str, char delimiter);
};