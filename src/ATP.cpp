#include "ATP.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

ATP::ATP() : root(nullptr), name("") {} 

ATP::ATP(const std::string& name) : root(nullptr), name(name) {} 

ATP::ATP(const ATP& other) : root(this->copy(other.root)), name(other.name) {}

ATP& ATP::operator = (const ATP& other)
{
    if (&other != this)
    {
        this->deallocate(this->root);
        this->root = this->copy(other.root);
    }

    return *this;
}

ATP::~ATP()
{
    this->deallocate(this->root);
}

void ATP::readHierarchy(std::map<std::string, std::vector<std::string>>& relationships, std::istream& input)
{
    std::string line;
    while (std::getline(input, line))
    {
        if (line == "")
        {
            break;
        }

        size_t pos = line.find('-');
        if (pos != std::string::npos)
        {
            std::string parent = line.substr(0, pos);
            std::string child = line.substr(pos + 1);

            relationships[parent].push_back(child);
        }
    }
}

void ATP::printToFile(std::istream& input)
{
    std::ofstream outputFile("../../output.txt");
    if (!outputFile.is_open())
    {
        std::cerr << "Error opening file: output.txt" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(input, line))
    {
        if (line == "")
        {
            break;
        }

        outputFile << line << std::endl;
    }

    outputFile.close();
}

void ATP::sortChildrenRecursively(Box* root)
{
    std::sort(root->children.begin(), root->children.end(),
              [](const Box* a, const Box* b) 
              {
                return a->data < b->data;
              });

    for (Box* child : root->children)
    {
        sortChildrenRecursively(child);
    }
}

Box* ATP::load(const std::string& objectName, const std::string& fileName)
{
    for (size_t i = 0; i < objectName.size(); i++)
    {
        if(!CommonMethods::isValidSymbol(objectName[i]))
        {
            std::cerr << objectName << " is invalid object name" << std::endl;
            std::exit(-1);
        }
    }

    std::map<std::string, std::vector<std::string>> relationships;

    if (fileName.empty())
    {
        std::string fileName1 = "../../output.txt";
        std::ifstream inputFile(fileName1);
        std::cout << "Enter " << objectName << " hierarchy.\n";
        printToFile(std::cin);
        
        if (FileUtils::areValidRelationsFromFile(fileName1))
        {
            readHierarchy(relationships, inputFile);
            this->name = objectName;
            inputFile.close();
        }
        else
        {
            FileUtils::ClearTextFiles(fileName1);
            return nullptr;
        } 
    }
    else
    {
        std::ifstream inputFile(fileName);
        if (!inputFile.is_open())
        {
            std::cerr << "Error opening file: " << fileName << std::endl;
        }

        if(FileUtils::areValidRelationsFromFile(fileName))
        {
            readHierarchy(relationships, inputFile);
            this->name = objectName;
            inputFile.close();
        }
        else
        {
            return nullptr;
        }
    }

    Box* root = constructTree("CEO_to", relationships);
    this->root = root;

    sortChildrenRecursively(root);

    return this->root;
}

std::string ATP::convertTreeToString(Box* root) 
{
    std::string result;

    if (!root)
        return result;

    for (std::size_t i = 0; i < root->children.size(); i++)
    {
        result += root->data + "-" + root->children[i]->data + "\n";
    }

    for (std::size_t i = 0; i < root->children.size(); i++)
    {
        result += convertTreeToString(root->children[i]);
    }

    return result;
}

Box* ATP::constructTree(const std::string& rootValue, const std::map<std::string, std::vector<std::string>>& relationships)
{
    Box* root = new Box(rootValue);
    constructTreeHelper(root, relationships, 0);
    return root;
}

void ATP::constructTreeHelper(Box* root, const std::map<std::string, std::vector<std::string>>& relationships, int depth)
{
    auto it = relationships.find(root->data);
    if (it != relationships.end())
    {
        for (const auto& childValue : it->second)
        {
            Box* child = new Box(childValue);
            root->children.push_back(child);
            constructTreeHelper(child, relationships, depth + 1);
        }
    }
}

void ATP::printHierarchy(Box* root, std::ostream& output, int depth)
{
    if (!root)
        return;

    for (int i = 0; i < depth; i++)
        output << " ";

    output << root->data << std::endl;

    for (std::size_t i = 0; i < root->children.size(); i++)
    {
        printHierarchy(root->children[i], output, depth + 1);
    }
}

Box* ATP::findEmployee(Box* root, const std::string& element)
{
    if (!root)
        return nullptr;

    if (root->data == element)
        return root;

    for (Box* child : root->children)
    {
        Box* result = findEmployee(child, element);
        if (result)
            return result;
    }

    return nullptr;
}

bool ATP::findEmployee(const std::string& element)
{
    Box* result = findEmployee(root, element);
    if (result)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ATP::save(const std::string& fileName)
{
    if (fileName.empty())
    {
        printHierarchy(root, std::cout);
    }
    else
    {
        std::ofstream outputFile(fileName);
        if (!outputFile.is_open())
        {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return;
        }

        printHierarchy(root, outputFile);
        outputFile.close();
    }
}

std::size_t ATP::numberOfChildren(const std::string &element)
{
    std::size_t numChildren = 0;
 
    if (!root)
        return 0;
 
    std::queue<Box*> q;
    q.push(root);
 
    while (!q.empty()) 
    {
        std::size_t n = q.size();
 
        while (n > 0) 
        {
            Box* p = q.front();
            q.pop();
            if (p->data == element) 
            {
                numChildren = static_cast<int>(p->children.size());
                return numChildren;
            }

            for (int i = 0; i < p->children.size(); i++)
                q.push(p->children[i]);
            n--;
        }
    }
    return numChildren;
}

std::size_t ATP::numEmployees(Box* root)
{
    if (!root)
    {
        return 0;
    }

    std::size_t count = 0;
    if (!root->children.empty())
    {
        for (const auto& child : root->children)
        {
            count += numEmployees(child);
        }
    }

    return 1 + count;
}

std::size_t ATP::numEmployees()
{
    if (!root)
    {
        return 0;
    }

    return numEmployees(root);
}

std::vector<std::string> ATP::findPath(Box* current, const std::string& employeeName)
{
    std::vector<std::string> path;
    findPathHelper(current, employeeName, path);
    return path;
}

bool ATP::findPathHelper(Box* current, const std::string& employeeName, std::vector<std::string>& path)
{
    if (!current)
    {
        return false;
    }

    path.push_back(current->data);

    if (current->data == employeeName)
    {
        return true;
    }

    for (Box* child : current->children)
    {
        if (findPathHelper(child, employeeName, path))
        {
            return true;
        }
    }

    path.pop_back();
    return false;
}

std::vector<std::string> ATP::getLeaves(const Box* root)
{
    std::vector<std::string> leaves;
    getLeavesHelper(root, leaves);
    return leaves;
}

void ATP::getLeavesHelper(const Box* current, std::vector<std::string>& leaves)
{
    if (!current)
    {
        return;
    }

    if (current->children.empty())
    {
        leaves.push_back(current->data);
    }
    else
    {
        for (const auto& child : current->children)
        {
            getLeavesHelper(child, leaves);
        }
    }
}

std::size_t ATP::sizeLongestPath(Box* current)
{
    std::vector<std::string> leaves = this->getLeaves(current);
    std::vector<std::string> longestPath;
    for (const auto& leaf : leaves)
    {
        std::vector<std::string> currentPath = this->findPath(current, leaf);

        if (currentPath.size() > longestPath.size())
        {
            longestPath = currentPath;
        }
    }

    return longestPath.size();
}

std::string ATP::manager(const std::string& employeeName)
{
    std::vector<std::string> path = findPath(root, employeeName);

    if (path.empty())
    {
        return "";
    }
    
    std::size_t size = path.size();

    if (employeeName == "CEO_to")
    {
        return employeeName;
    }
    return path[size - 2];
}

std::vector<std::string> ATP::getAllEmployees(Box* root)
{
    std::vector<std::string> employees;
    getAllEmployeesHelper(root, employees);
    return employees;
}

void ATP::getAllEmployeesHelper(Box* root, std::vector<std::string>& employees)
{
    if (!root)
    {
        return;
    }

    employees.push_back(root->data);

    for (const auto& child : root->children)
    {
        getAllEmployeesHelper(child, employees);
    }
}

std::size_t ATP::overloaded()
{
    std::vector<std::string> employees = getAllEmployees(root);

    std::size_t countEmployees = 0;

    for (const auto& employee : employees)
    {
        std::size_t numberOfDirectChildren = numberOfChildren(employee);
        std::size_t numberOfIndirectChildren = numIndirectEmployees(employee);

        std::size_t numberOfChildren = numberOfDirectChildren + numberOfIndirectChildren;

        if (numberOfChildren > 20)
        {
            ++countEmployees;
        }
    }

    return countEmployees;
}

void ATP::erase(Box*& root, const std::string &element)
{
    if (!root)
    {
        return;
    }
    
    auto it = std::find_if(root->children.begin(), root->children.end(),
        [element](const Box* child) { return child->data == element; });

    if (it != root->children.end())
    {
        Box* removedChild = *it;
        root->children.erase(it);

        for (Box* grandChild : removedChild->children)
        {
            root->children.push_back(grandChild);
        }

        delete removedChild;
    }
    else
    {
        for (Box* child : root->children)
        {
            erase(child, element);
        }
    }
}

void ATP::erase(const std::string &element)
{
    erase(root, element);
}

void ATP::hire(Box* root, const std::string& employee, const std::string& newManager)
{
    Box* employeeNode = findEmployee(root, employee);
    Box* newManagerNode = findEmployee(root, newManager);
    if (employeeNode)
    {
        this->erase(root, employee);
        newManagerNode->children.push_back(employeeNode);
    }
    else
    {
        Box* newEmployeeNode = new Box(employee);
        newManagerNode->children.push_back(newEmployeeNode);
    }
}

void ATP::hire(const std::string& employee, const std::string& newManager)
{
    hire(root, employee, newManager);
}

std::size_t ATP::numIndirectEmployees(Box* root, const std::string& manager)
{
    Box* employeeNode = findEmployee(root, manager);
    if (!employeeNode)
    {
        return 0;
    }

    std::size_t count = 0;

    std::queue<Box*> nodeQueue;
    nodeQueue.push(employeeNode);

    while (!nodeQueue.empty())
    {
        Box* currentNode = nodeQueue.front();
        nodeQueue.pop();

        for (const auto& child : currentNode->children)
        {
            count += child->children.size();
            nodeQueue.push(child);
        }
    }

    return count;
}

std::size_t ATP::numIndirectEmployees(const std::string& manager)
{
    return numIndirectEmployees(root, manager);
}

std::size_t ATP::salary(const std::string& employee)
{
    std::size_t numberOfDirectChildren = numberOfChildren(employee);
    std::size_t numberOfIndirectChildren = numIndirectEmployees(employee);
    std::size_t salary = 500 * numberOfDirectChildren + 50 * numberOfIndirectChildren; 
    return salary;
}

void ATP::incorporate()
{
    if (!root)
    {
        std::cout << "Object not found." << std::endl;
        return;
    }

    incorporateHierarchy(root);
}

void ATP::incorporateHierarchy(Box* root)
{
    if (!root)
    {
        return;
    }

    if (root->children.size() >= 2)
    {
        std::string highestSalaryEmployee = findHighestSalaryEmployee(root);

        Box* newRoot = new Box(highestSalaryEmployee);

        newRoot->children = root->children;
        erase(newRoot, highestSalaryEmployee);

        root->children.clear();
        root->children.push_back(newRoot);

        for (auto& child : newRoot->children)
        {
            incorporateHierarchy(child);
        }
    }
    else
    {
        for (auto& child : root->children)
        {
            incorporateHierarchy(child);
        }
    }
}

std::string ATP::findHighestSalaryEmployee(Box* root)
{
    if (!root || root->children.empty())
    {
        return nullptr;
    }

    Box* highestSalaryEmployee = root->children.front();

    for (Box* employee : root->children)
    {
        std::size_t salaryEmployee = salary(employee->data);
        std::size_t salaryHighest = salary(highestSalaryEmployee->data);

        if (salaryEmployee > salaryHighest ||
            (salaryEmployee == salaryHighest && employee->data < highestSalaryEmployee->data))
        {
            highestSalaryEmployee = employee;
        }
    }

    return highestSalaryEmployee->data;
}

std::vector<std::string> ATP::atLevelRecursive(Box* root, std::size_t targetLevel, std::size_t currentLevel)
{
    std::vector<std::string> result;
    if (!root)
    {
        return {};
    }

    if (currentLevel % 2 == 1 && currentLevel > 1 && currentLevel <= targetLevel && numberOfChildren(root->data) > 0)
    {
        result.push_back(root->data);
    }

    for (auto& child : root->children)
    {
        auto childResult = atLevelRecursive(child, targetLevel, currentLevel + 1);
        result.insert(result.end(), childResult.begin(), childResult.end());
    }

    return result;
}

void ATP::modernize()
{
    std::vector<std::string> result = atLevelRecursive(this->root, 3, 0);

    for (const auto& element : result)
    {
        std::string father = manager(element);
        std::string grandpa = manager(father);

        erase(this->root, element);
        hire(this->root, element, grandpa);
    }
}