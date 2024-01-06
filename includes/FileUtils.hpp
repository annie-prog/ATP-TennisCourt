#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <iostream>
#include "Common.hpp"

class FileUtils 
{
private:
    static bool isUnique(const std::string& employee, const std::vector<std::string>& employees) 
    {
        for (const std::string& e : employees) 
        {
            if (e == employee) 
            {
                std::cout << "Employee '" << e << "' encountered more than once as a subordinate." << std::endl;
                return false;
            }
        }
        return true;
    }
public: 
    static void ClearTextFiles(const std::string& filename);
    static bool areValidRelation(const std::string& relation);
    static bool areValidRelationsFromFile(const std::string& filename);
};