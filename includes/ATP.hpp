#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include "Box.hpp"
#include "Common.hpp"
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
        for (std::size_t i = 0; i < root->children.size(); ++i)
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

        for (std::size_t i = 0; i < root->children.size(); ++i)
        {
            deallocate(root->children[i]);
        }
        delete root;
    }

    void readHierarchy(std::map<std::string, std::vector<std::string>>& relationships, std::istream& input);
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

    Box* load(const std::string& objectName, const std::string& fileName = "");
    void sortChildrenRecursively(Box* root);
    void printToFile(std::istream& input);
    Box* constructTree(const std::string& rootValue, const std::map<std::string, std::vector<std::string>>& relationships);
    void constructTreeHelper(Box* root, const std::map<std::string, std::vector<std::string>>& relationships, int depth);

    std::string convertTreeToString(Box* root); 

    Box* findEmployee(Box* root, const std::string& element);
    bool findEmployee(const std::string& objectName, const std::string &element);

    void save(const std::string& objectName, const std::string& fileName);
    void printHierarchy(Box* root, std::ostream& output, int depth = 0);

    std::size_t numberOfChildren(const std::string &objectName, const std::string &x);

    std::vector<std::string> findPath(Box* current, const std::string& employeeName);
    bool findPathHelper(Box* current, const std::string& employeeName, std::vector<std::string>& path);

    std::vector<std::string> getLeaves(const Box* root);
    void getLeavesHelper(const Box* current, std::vector<std::string>& leaves);

    std::size_t sizeLongestPath(Box* current);

    std::string manager(const std::string& objectName, const std::string& employeeName);

    std::size_t numEmployees(const std::string &objectName);
    std::size_t numEmployees(const std::string& objectName, Box* root);

    std::size_t overloaded(const std::string& objectName);
    std::vector<std::string> getAllEmployees(Box* root);
    void getAllEmployeesHelper(Box* root, std::vector<std::string>& employees);

    void erase(Box*& root, const std::string &element);
    void hire(Box* root, const std::string& objectName, const std::string& employee, const std::string& newManager);

    std::size_t salary(Box* root, const std::string& objectName, const std::string& employee);

    std::size_t numIndirectEmployees(const std::string& objectName, Box* root, const std::string& manager);

    void incorporate(const std::string& objectName);
    void incorporateHierarchy(Box* root, const std::string& objectName);
    std::string findHighestSalaryEmployee(Box* root, const std::string& objectName);

    std::vector<std::string> atLevelRecursive(Box* root, std::size_t targetLevel, std::size_t currentLevel, const std::string& objectName);
    void modernize(Box* root, const std::string& objectName);

    Box* findHigherLeader(Box* root, std::size_t currentLevel) const;
    Box* findParent(Box* root, const std::string& data) const;
};