#pragma once
#include <string>
#include <vector>

struct Box
{
    std::string data;
    std::vector<Box*> children;

    Box(const std::string& data, const std::vector<Box*>& children = std::vector<Box*>())
        : data(data), children(children) {}
};