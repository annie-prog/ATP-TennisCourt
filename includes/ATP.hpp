#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include "Box.hpp"
#include "FileUtils.hpp"

class ATP
{
private:
    Box* root;
    std::string name;

    Box* copy(Box* root)
    {
        if (!root)
        {
            return nullptr;
        }

        std::vector<Box*> buffer;
        for (std::size_t i = 0; i < root->children.size(); i++)
        {
            buffer.push_back(copy(root->children[i]));
        }

        return new Box(root->data, buffer);
    }

    void deallocate(Box* root)
    {
        if (!root)
        {
            return;
        }

        for (std::size_t i = 0; i < root->children.size(); i++)
        {
            deallocate(root->children[i]);
        }
        delete root;
    }

    void readHierarchy(std::map<std::string, std::vector<std::string>>& relationships, std::istream& input);
    void sortChildrenRecursively(Box* root);
    void printToFile(std::istream& input);
    Box* constructTree(const std::string& rootData, const std::map<std::string, std::vector<std::string>>& relationships);
    void constructTreeHelper(Box* root, const std::map<std::string, std::vector<std::string>>& relationships, int depth);

    Box* findEmployee(Box* root, const std::string& element);

    bool findPathHelper(Box* root, const std::string& employeeName, std::vector<std::string>& path);

    std::size_t numEmployees(Box* root);

    std::vector<std::string> getLeaves(Box* root);
    void getLeavesHelper(Box* root, std::vector<std::string>& leaves);

    void getAllEmployeesHelper(Box* root, std::vector<std::string>& employees);

    void erase(Box*& root, const std::string &element);
    void hire(Box* root, const std::string& employee, const std::string& newManager);

    std::size_t numIndirectEmployees(Box* root, const std::string& manager);
    std::size_t numIndirectEmployees(const std::string& manager);

    void incorporateHierarchy(Box* root);
    std::string findHighestSalaryEmployee(Box* root);

    std::vector<std::string> atLevelRecursive(Box* root, std::size_t targetLevel, std::size_t currentLevel);

public:
    ATP();
    ATP(const std::string& name);
    ATP(const ATP& other);
    ATP& operator = (const ATP& other);
    ~ATP();

    std::string getName()
    {
        return this->name;
    }
    
    Box* getRoot()
    {
        return this->root;
    }

    Box* load(const std::string& objectName, const std::string& fileName = "");
    std::string convertTreeToString(Box* root); 

    bool findEmployee(const std::string &element);

    void save(const std::string& fileName = "");
    void printHierarchy(Box* root, std::ostream& output, int depth = 0);

    std::size_t numberOfChildren(const std::string &element);

    std::vector<std::string> findPath(Box* root, const std::string& employeeName);
    std::size_t sizeLongestPath(Box* root);

    std::string manager(const std::string& employeeName);

    std::size_t numEmployees();
    std::vector<std::string> getAllEmployees(Box* root);
    std::size_t overloaded();

    void erase(const std::string &element);
    void hire(const std::string& employee, const std::string& newManager);

    std::size_t salary(const std::string& employee);

    void incorporate();
    void modernize();

    Box* join(Box* root1, Box* root2);
};