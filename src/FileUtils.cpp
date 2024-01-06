#include "FileUtils.hpp"

std::unordered_map<std::string, std::string> subordinateMap; // map for all relations

void FileUtils::ClearTextFiles(const std::string& filename) 
{
    std::ofstream file(filename);
    file.close();
}

bool FileUtils::areValidRelation(const std::string& relation) 
{
    std::vector<std::string> encounteredEmployees; // vector for all employees so we can check if we have encounter an employee more than once

    std::string manager, employee;
    bool separatorFound = false;

    for (char ch : relation) 
    {
        if (ch == '-') 
        {
            if (separatorFound) 
            {
                std::cout << "Invalid relation format: " << relation << std::endl;
                return false;
            }
            separatorFound = true;
        } 
        else if (!separatorFound) 
        {
            if (!CommonMethods::isValidSymbol(ch)) 
            {
                return false;
            }
            manager += ch;
        } 
        else 
        {
            if (!CommonMethods::isValidSymbol(ch))  
            {
                return false;
            }
            employee += ch;
        }
    }

    if (manager.empty() || employee.empty() || !separatorFound || !isUnique(employee, encounteredEmployees)) 
    {
        return false;
    }

    encounteredEmployees.push_back(employee);
    subordinateMap[employee] = manager;

    return true;
}

bool FileUtils::areValidRelationsFromFile(const std::string& filename) 
{
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string relation;
    while (std::getline(file, relation)) 
    {
        if (!areValidRelation(relation)) 
        {
            std::cout << "Invalid relation: " << relation << std::endl;
            file.close();
            return false;
        }
    }

    for (const auto& entry : subordinateMap) 
    {
        const std::string& subordinate = entry.first;
        const std::string& manager = entry.second;

        if (subordinateMap.find(manager) == subordinateMap.end() && manager != "CEO_to") 
        {
            std::cout << subordinate << " is subordinate to " << manager << ", but " << manager << " is not found." << std::endl;
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}